// tests/test_stack.cpp
// Exhaustive unit tests for Stack ADT (stack.h / stack.cpp)
// exit 0 = all pass, exit 1 = any failure

#include "../stack.h"
#include <iostream>
#include <string>
#include <stdexcept>

static int g_passed = 0, g_failed = 0;

void test(const std::string& name, bool cond) {
    if (cond) { std::cout << "[PASS] " << name << "\n"; ++g_passed; }
    else       { std::cout << "[FAIL] " << name << "\n"; ++g_failed; }
}

template<typename Fn>
bool throws(Fn fn) {
    try { fn(); return false; }
    catch (...) { return true; }
}

int main() {
    std::cout << "=== Stack Unit Tests ===\n\n";

    // §1. Initialization
    Stack s;
    init(&s);
    test("§1.1 init: isEmpty",         isEmpty(&s));
    test("§1.2 init: !isFull",        !isFull(&s));
    test("§1.3 init: peek throws",     throws([&]{ peek(&s); }));
    test("§1.4 init: pop throws",      throws([&]{ pop(&s); }));

    // §2. Single push/pop
    push(&s, 42);
    test("§2.1 push(42): !isEmpty",   !isEmpty(&s));
    test("§2.2 push(42): !isFull",    !isFull(&s));
    test("§2.3 push(42): peek==42",    peek(&s) == 42);
    pop(&s);
    test("§2.4 after pop: isEmpty",    isEmpty(&s));
    test("§2.5 after pop: peek throws",throws([&]{ peek(&s); }));
    test("§2.6 after pop: pop throws", throws([&]{ pop(&s); }));

    // §3. LIFO — 3 elements
    push(&s, 10); push(&s, 20); push(&s, 30);
    test("§3.1 peek==30", peek(&s)==30); pop(&s);
    test("§3.2 peek==20", peek(&s)==20); pop(&s);
    test("§3.3 peek==10", peek(&s)==10); pop(&s);
    test("§3.4 empty after 3 pops", isEmpty(&s));

    // §4. LIFO — 10 elements sequential
    for (int i = 1; i <= 10; ++i) push(&s, i * 100);
    for (int i = 10; i >= 1; --i) {
        test("§4 LIFO peek==" + std::to_string(i*100), peek(&s) == i*100);
        pop(&s);
    }
    test("§4.end empty", isEmpty(&s));

    // §5. Boundary values
    push(&s, -1000); push(&s, 0); push(&s, 1000);
    test("§5.1 peek==1000",  peek(&s)==1000);  pop(&s);
    test("§5.2 peek==0",     peek(&s)==0);     pop(&s);
    test("§5.3 peek==-1000", peek(&s)==-1000); pop(&s);

    // §6. Duplicate values
    push(&s, 7); push(&s, 7); push(&s, 7);
    test("§6.1 dup top1==7", peek(&s)==7); pop(&s);
    test("§6.2 dup top2==7", peek(&s)==7); pop(&s);
    test("§6.3 dup top3==7", peek(&s)==7); pop(&s);
    test("§6.4 empty after dups", isEmpty(&s));

    // §7. Interleaved push/pop
    push(&s, 1);
    test("§7.1 peek==1", peek(&s)==1);
    push(&s, 2);
    test("§7.2 peek==2", peek(&s)==2);
    pop(&s);
    test("§7.3 back to peek==1", peek(&s)==1);
    push(&s, 3);
    test("§7.4 peek==3", peek(&s)==3);
    pop(&s); pop(&s);
    test("§7.5 empty", isEmpty(&s));

    // §8. isFull at MAX capacity
    for (int i = 0; i < MAX; ++i) push(&s, i);
    test("§8.1 isFull",           isFull(&s));
    test("§8.2 !isEmpty",        !isEmpty(&s));
    test("§8.3 push-full throws", throws([&]{ push(&s, 999); }));
    test("§8.4 peek is last",     peek(&s) == MAX - 1);

    // §9. Pop all from full, verify each value
    for (int i = MAX - 1; i >= 0; --i) {
        test("§9 drain peek==" + std::to_string(i), peek(&s) == i);
        pop(&s);
    }
    test("§9.end empty after full drain", isEmpty(&s));

    // §10. Re-init resets
    push(&s, 55); push(&s, 66);
    init(&s);
    test("§10.1 isEmpty after re-init",        isEmpty(&s));
    test("§10.2 peek throws after re-init",    throws([&]{ peek(&s); }));
    test("§10.3 pop throws after re-init",     throws([&]{ pop(&s); }));
    push(&s, 99);
    test("§10.4 push after re-init peek==99",  peek(&s)==99);
    pop(&s);
    test("§10.5 empty after pop post-reinit",  isEmpty(&s));

    // §11. Multiple independent stacks
    Stack s2;
    init(&s2);
    push(&s, 100); push(&s2, 200);
    test("§11.1 s peek==100",  peek(&s)==100);
    test("§11.2 s2 peek==200", peek(&s2)==200);
    push(&s, 101); push(&s2, 201);
    test("§11.3 s peek==101",  peek(&s)==101);
    test("§11.4 s2 peek==201", peek(&s2)==201);
    pop(&s); pop(&s);
    pop(&s2); pop(&s2);
    test("§11.5 s empty",  isEmpty(&s));
    test("§11.6 s2 empty", isEmpty(&s2));

    // §12. isFull/isEmpty boundary dance
    for (int i = 0; i < MAX; ++i) push(&s, i);
    test("§12.1 isFull",               isFull(&s));
    pop(&s);
    test("§12.2 !isFull after 1 pop",  !isFull(&s));
    push(&s, 9999);
    test("§12.3 isFull after re-fill", isFull(&s));
    test("§12.4 push still throws",    throws([&]{ push(&s, 1); }));

    // §13. Drain full stack, refill with negatives
    while (!isEmpty(&s)) pop(&s);
    test("§13.1 drained",   isEmpty(&s));
    for (int i = 0; i < MAX; ++i) push(&s, -i);
    test("§13.2 full again",          isFull(&s));
    test("§13.3 top is -(MAX-1)",     peek(&s) == -(MAX-1));
    int expected_neg = -(MAX-1);
    pop(&s);
    test("§13.4 after 1 pop: -(MAX-2)", peek(&s) == expected_neg + 1);

    // §14. Negative values LIFO order
    while (!isEmpty(&s)) pop(&s);
    push(&s, -1); push(&s, -2); push(&s, -3);
    test("§14.1 peek==-3", peek(&s)==-3); pop(&s);
    test("§14.2 peek==-2", peek(&s)==-2); pop(&s);
    test("§14.3 peek==-1", peek(&s)==-1); pop(&s);

    // §15. Zero-only stack
    push(&s, 0); push(&s, 0); push(&s, 0);
    test("§15.1 peek==0 #1", peek(&s)==0); pop(&s);
    test("§15.2 peek==0 #2", peek(&s)==0); pop(&s);
    test("§15.3 peek==0 #3", peek(&s)==0); pop(&s);
    test("§15.4 empty",      isEmpty(&s));

    // §16. Mixed positive/negative interleaved
    push(&s, -500); push(&s, 500); push(&s, -250); push(&s, 250);
    test("§16.1 peek==250",  peek(&s)==250);  pop(&s);
    test("§16.2 peek==-250", peek(&s)==-250); pop(&s);
    test("§16.3 peek==500",  peek(&s)==500);  pop(&s);
    test("§16.4 peek==-500", peek(&s)==-500); pop(&s);

    // §17. Exception is actually catchable (not crash/abort)
    bool caught_pop = false, caught_peek = false, caught_full = false;
    try { pop(&s); }  catch (...) { caught_pop = true; }
    test("§17.1 pop-empty catchable", caught_pop);

    try { peek(&s); } catch (...) { caught_peek = true; }
    test("§17.2 peek-empty catchable", caught_peek);

    for (int i = 0; i < MAX; ++i) push(&s, i);
    try { push(&s, 1); } catch (...) { caught_full = true; }
    test("§17.3 push-full catchable", caught_full);

    // §18. Multiple pops exactly to empty, then one more throws
    while (!isEmpty(&s)) pop(&s);
    push(&s, 1); push(&s, 2);
    pop(&s); pop(&s);
    test("§18.1 empty exactly", isEmpty(&s));
    test("§18.2 one-more pop throws", throws([&]{ pop(&s); }));

    // §19. Peek does not modify stack
    push(&s, 77);
    test("§19.1 peek==77",       peek(&s)==77);
    test("§19.2 peek==77 again", peek(&s)==77);
    test("§19.3 !isEmpty",      !isEmpty(&s));
    pop(&s);
    test("§19.4 empty after pop", isEmpty(&s));

    // §20. Large value stress
    push(&s, 999999); push(&s, -999999);
    test("§20.1 peek==-999999", peek(&s)==-999999); pop(&s);
    test("§20.2 peek==999999",  peek(&s)==999999);  pop(&s);

    // Summary
    std::cout << "\n=== " << g_passed << " / " << (g_passed + g_failed)
              << " tests passed ===\n";
    return (g_failed == 0) ? 0 : 1;
}
