// tests/test_queue.cpp
// Exhaustive unit tests for Queue ADT (queue.h / queue.cpp)
// exit 0 = all pass, exit 1 = any failure

#include "../queue.h"
#include <iostream>
#include <string>

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
    std::cout << "=== Queue Unit Tests ===\n\n";

    // §1. Initialization
    Queue q;
    init(&q);
    test("§1.1 init: isEmpty",          isEmpty(&q));
    test("§1.2 init: !isFull",         !isFull(&q));
    test("§1.3 init: front throws",     throws([&]{ front(&q); }));
    test("§1.4 init: back throws",      throws([&]{ back(&q); }));
    test("§1.5 init: dequeue throws",   throws([&]{ dequeue(&q); }));

    // §2. Single enqueue/dequeue
    enqueue(&q, 42);
    test("§2.1 enqueue(42): !isEmpty",  !isEmpty(&q));
    test("§2.2 enqueue(42): !isFull",   !isFull(&q));
    test("§2.3 front==42",               front(&q) == 42);
    test("§2.4 back==42",                back(&q)  == 42);
    dequeue(&q);
    test("§2.5 isEmpty after dequeue",   isEmpty(&q));
    test("§2.6 front throws after deq",  throws([&]{ front(&q); }));
    test("§2.7 back throws after deq",   throws([&]{ back(&q);  }));
    test("§2.8 dequeue throws after deq",throws([&]{ dequeue(&q); }));

    // §3. FIFO ordering — 3 elements
    enqueue(&q, 10); enqueue(&q, 20); enqueue(&q, 30);
    test("§3.1 front==10", front(&q)==10);
    test("§3.2 back==30",  back(&q)==30);
    dequeue(&q);
    test("§3.3 front==20 after deq", front(&q)==20);
    test("§3.4 back==30 unchanged",  back(&q)==30);
    dequeue(&q);
    test("§3.5 front==30", front(&q)==30);
    test("§3.6 back==30",  back(&q)==30);
    dequeue(&q);
    test("§3.7 isEmpty after 3 dequeues", isEmpty(&q));

    // §4. FIFO — 10 elements sequential
    for (int i = 1; i <= 10; ++i) enqueue(&q, i * 100);
    for (int i = 1; i <= 10; ++i) {
        test("§4 FIFO front==" + std::to_string(i*100), front(&q) == i*100);
        dequeue(&q);
    }
    test("§4.end empty", isEmpty(&q));

    // §5. front and back always correct
    enqueue(&q, 1); enqueue(&q, 2); enqueue(&q, 3); enqueue(&q, 4); enqueue(&q, 5);
    test("§5.1 front==1", front(&q)==1);
    test("§5.2 back==5",  back(&q)==5);
    dequeue(&q);
    test("§5.3 front==2", front(&q)==2);
    test("§5.4 back==5",  back(&q)==5);
    dequeue(&q); dequeue(&q);
    test("§5.5 front==4", front(&q)==4);
    test("§5.6 back==5",  back(&q)==5);
    dequeue(&q);
    test("§5.7 front==5 == back==5", front(&q)==5 && back(&q)==5);
    dequeue(&q);
    test("§5.8 isEmpty", isEmpty(&q));

    // §6. Boundary values
    enqueue(&q, -1000); enqueue(&q, 0); enqueue(&q, 1000);
    test("§6.1 front==-1000", front(&q)==-1000);
    test("§6.2 back==1000",   back(&q)==1000);
    dequeue(&q);
    test("§6.3 front==0",     front(&q)==0);
    dequeue(&q);
    test("§6.4 front==1000 == back", front(&q)==1000 && back(&q)==1000);
    dequeue(&q);
    test("§6.5 empty", isEmpty(&q));

    // §7. Duplicate values
    enqueue(&q, 5); enqueue(&q, 5); enqueue(&q, 5);
    test("§7.1 front==5", front(&q)==5);
    test("§7.2 back==5",  back(&q)==5);
    dequeue(&q);
    test("§7.3 front==5 still", front(&q)==5);
    dequeue(&q); dequeue(&q);
    test("§7.4 empty after dups", isEmpty(&q));

    // §8. isFull at MAX capacity
    for (int i = 0; i < MAX; ++i) enqueue(&q, i);
    test("§8.1 isFull",             isFull(&q));
    test("§8.2 !isEmpty",          !isEmpty(&q));
    test("§8.3 enqueue-full throws",throws([&]{ enqueue(&q, 999); }));
    test("§8.4 front==0",           front(&q) == 0);
    test("§8.5 back==MAX-1",        back(&q) == MAX - 1);

    // §9. Drain full, check FIFO order
    for (int i = 0; i < MAX; ++i) {
        test("§9 drain front==" + std::to_string(i), front(&q) == i);
        dequeue(&q);
    }
    test("§9.end empty after full drain", isEmpty(&q));

    // §10. Re-init resets
    enqueue(&q, 55); enqueue(&q, 66);
    init(&q);
    test("§10.1 isEmpty after re-init",         isEmpty(&q));
    test("§10.2 front throws after re-init",    throws([&]{ front(&q);   }));
    test("§10.3 back throws after re-init",     throws([&]{ back(&q);    }));
    test("§10.4 dequeue throws after re-init",  throws([&]{ dequeue(&q); }));
    enqueue(&q, 77);
    test("§10.5 enqueue after re-init ok",      front(&q)==77 && back(&q)==77);
    dequeue(&q);
    test("§10.6 empty after post-reinit pop",   isEmpty(&q));

    // §11. Multiple independent queues
    Queue q2;
    init(&q2);
    enqueue(&q, 100); enqueue(&q2, 200);
    test("§11.1 q front==100",  front(&q)==100);
    test("§11.2 q2 front==200", front(&q2)==200);
    enqueue(&q, 101); enqueue(&q2, 201);
    test("§11.3 q back==101",   back(&q)==101);
    test("§11.4 q2 back==201",  back(&q2)==201);
    dequeue(&q); dequeue(&q);
    dequeue(&q2); dequeue(&q2);
    test("§11.5 q empty",  isEmpty(&q));
    test("§11.6 q2 empty", isEmpty(&q2));

    // §12. isFull/isEmpty boundary dance
    for (int i = 0; i < MAX; ++i) enqueue(&q, i);
    test("§12.1 isFull",                isFull(&q));
    dequeue(&q);
    test("§12.2 !isFull after 1 deq",  !isFull(&q));
    enqueue(&q, 9999);
    test("§12.3 isFull after re-fill",  isFull(&q));
    test("§12.4 enqueue still throws",  throws([&]{ enqueue(&q, 1); }));

    // §13. Drain full, refill negatives
    while (!isEmpty(&q)) dequeue(&q);
    test("§13.1 drained", isEmpty(&q));
    for (int i = 0; i < MAX; ++i) enqueue(&q, -i);
    test("§13.2 isFull",        isFull(&q));
    test("§13.3 front==0",      front(&q) == 0);
    test("§13.4 back==-(MAX-1)",back(&q) == -(MAX - 1));

    // §14. Negative values FIFO
    while (!isEmpty(&q)) dequeue(&q);
    enqueue(&q, -3); enqueue(&q, -2); enqueue(&q, -1);
    test("§14.1 front==-3", front(&q)==-3); dequeue(&q);
    test("§14.2 front==-2", front(&q)==-2); dequeue(&q);
    test("§14.3 front==-1", front(&q)==-1); dequeue(&q);

    // §15. Zero-only queue
    enqueue(&q, 0); enqueue(&q, 0); enqueue(&q, 0);
    test("§15.1 front==0 #1", front(&q)==0); dequeue(&q);
    test("§15.2 front==0 #2", front(&q)==0); dequeue(&q);
    test("§15.3 front==0 #3", front(&q)==0); dequeue(&q);
    test("§15.4 empty", isEmpty(&q));

    // §16. Interleaved enqueue/dequeue mix
    enqueue(&q, 1); enqueue(&q, 2);
    dequeue(&q);
    enqueue(&q, 3);
    dequeue(&q);
    enqueue(&q, 4); enqueue(&q, 5);
    test("§16.1 front==3", front(&q)==3);
    test("§16.2 back==5",  back(&q)==5);
    dequeue(&q); dequeue(&q); dequeue(&q);
    test("§16.3 empty after interleaved", isEmpty(&q));

    // §17. front does not modify queue
    enqueue(&q, 88);
    test("§17.1 front==88",       front(&q)==88);
    test("§17.2 front==88 again", front(&q)==88);
    test("§17.3 !isEmpty",       !isEmpty(&q));
    dequeue(&q);
    test("§17.4 empty after dequeue", isEmpty(&q));

    // §18. back does not modify queue
    enqueue(&q, 11); enqueue(&q, 22);
    test("§18.1 back==22",       back(&q)==22);
    test("§18.2 back==22 again", back(&q)==22);
    test("§18.3 front still 11", front(&q)==11);
    dequeue(&q); dequeue(&q);
    test("§18.4 empty", isEmpty(&q));

    // §19. Exception catchable
    bool e1=false, e2=false, e3=false, e4=false;
    try { dequeue(&q); } catch(...){ e1=true; }
    test("§19.1 dequeue-empty catchable", e1);
    try { front(&q);   } catch(...){ e2=true; }
    test("§19.2 front-empty catchable",   e2);
    try { back(&q);    } catch(...){ e3=true; }
    test("§19.3 back-empty catchable",    e3);
    for (int i=0; i<MAX; ++i) enqueue(&q, i);
    try { enqueue(&q,1); } catch(...){ e4=true; }
    test("§19.4 enqueue-full catchable",  e4);

    // §20. Exactly to empty then one more throws
    while (!isEmpty(&q)) dequeue(&q);
    enqueue(&q, 1); enqueue(&q, 2);
    dequeue(&q); dequeue(&q);
    test("§20.1 exact empty",            isEmpty(&q));
    test("§20.2 dequeue throws exactly", throws([&]{ dequeue(&q); }));

    // Summary
    std::cout << "\n=== " << g_passed << " / " << (g_passed + g_failed)
              << " tests passed ===\n";
    return (g_failed == 0) ? 0 : 1;
}
