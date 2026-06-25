// tests/test_single_linked_list.cpp
// Exhaustive unit tests for SingleLinkedList (circular)
// exit 0 = all pass, exit 1 = any failure

#include "../single_linked_list.h"
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

static SingleLinkedList make(std::initializer_list<int> vals) {
    SingleLinkedList l;
    l.init();
    for (int v : vals) l.add_back(v);
    return l;
}

int main() {
    std::cout << "=== Single Linked List Unit Tests ===\n\n";

    // ─────────────────────────────────────────
    // §1. init & is_empty
    // ─────────────────────────────────────────
    {
        SingleLinkedList l; l.init();
        test("§1.1 init: is_empty",       l.is_empty());
        test("§1.2 init: size==0",         l.size == 0);
        test("§1.3 init: head==nullptr",   l.head == nullptr);
        test("§1.4 init: tail==nullptr",   l.tail == nullptr);
        l.add_front(1);
        test("§1.5 not empty after add",  !l.is_empty());
    }

    // ─────────────────────────────────────────
    // §2. add_front
    // ─────────────────────────────────────────
    {
        SingleLinkedList l; l.init();
        l.add_front(42);
        test("§2.1  single: get(0)==42",               l.get(0) == 42);
        test("§2.2  single: size==1",                  l.size == 1);
        test("§2.3  single: circular tail->next==head",l.tail->next == l.head);

        l.add_front(99);
        test("§2.4  two: get(0)==99",                  l.get(0) == 99);
        test("§2.5  two: get(1)==42",                  l.get(1) == 42);
        test("§2.6  two: circular",                    l.tail->next == l.head);

        l.add_front(1);
        test("§2.7  three: get(0)==1",                 l.get(0) == 1);
        test("§2.8  three: order 1,99,42",             l.get(1)==99 && l.get(2)==42);
        test("§2.9  three: size==3",                   l.size == 3);
        test("§2.10 three: circular",                  l.tail->next == l.head);

        SingleLinkedList l2; l2.init();
        l2.add_front(-7);
        test("§2.11 negative value",                   l2.get(0) == -7);
        l2.add_front(0);
        test("§2.12 zero value at front",              l2.get(0) == 0);

        SingleLinkedList l3; l3.init();
        for (int i = 0; i < 10; i++) l3.add_front(i);
        test("§2.13 x10: size==10",                    l3.size == 10);
        test("§2.14 x10: circular",                    l3.tail->next == l3.head);
        test("§2.15 x10: head->data==9",               l3.head->data == 9);
    }

    // ─────────────────────────────────────────
    // §3. add_back
    // ─────────────────────────────────────────
    {
        SingleLinkedList l; l.init();
        l.add_back(7);
        test("§3.1  single: get(0)==7",                l.get(0) == 7);
        test("§3.2  single: size==1",                  l.size == 1);
        test("§3.3  single: circular",                 l.tail->next == l.head);
        test("§3.4  single: head==tail",               l.head == l.tail);

        l.add_back(8);
        test("§3.5  two: get(0)==7 get(1)==8",         l.get(0)==7 && l.get(1)==8);
        test("§3.6  two: tail->data==8",               l.tail->data == 8);
        test("§3.7  two: circular",                    l.tail->next == l.head);

        SingleLinkedList l2; l2.init();
        for (int i = 0; i < 5; i++) l2.add_back(i * 10);
        test("§3.8  seq x5: get(0)==0",                l2.get(0) == 0);
        test("§3.9  seq x5: get(4)==40",               l2.get(4) == 40);
        test("§3.10 seq x5: size==5",                  l2.size == 5);
        test("§3.11 seq x5: circular",                 l2.tail->next == l2.head);

        SingleLinkedList l3; l3.init();
        l3.add_front(2); l3.add_back(3); l3.add_front(1);
        test("§3.12 mixed: get(0)==1",                 l3.get(0) == 1);
        test("§3.13 mixed: get(1)==2",                 l3.get(1) == 2);
        test("§3.14 mixed: get(2)==3",                 l3.get(2) == 3);
        test("§3.15 mixed: circular",                  l3.tail->next == l3.head);
    }

    // ─────────────────────────────────────────
    // §4. add_idx
    // ─────────────────────────────────────────
    {
        SingleLinkedList l = make({2,3});
        l.add_idx(1, 0);
        test("§4.1  at front: get(0)==1",              l.get(0) == 1);

        SingleLinkedList l2 = make({1,2});
        l2.add_idx(3, 2);
        test("§4.2  at back: get(2)==3",               l2.get(2) == 3);

        SingleLinkedList l3 = make({1,3});
        l3.add_idx(2, 1);
        test("§4.3  at middle: get(1)==2",             l3.get(1) == 2);
        test("§4.4  at middle: size==3",               l3.size == 3);
        test("§4.5  at middle: circular",              l3.tail->next == l3.head);

        SingleLinkedList l4 = make({1,2,4,5});
        l4.add_idx(3, 2);
        bool seq = true;
        for (int i = 0; i < 5; i++) seq &= (l4.get(i) == i+1);
        test("§4.6  order after insert correct",       seq);

        SingleLinkedList l5 = make({1,2});
        test("§4.7  out-of-range throws",              throws([&]{ l5.add_idx(5,10); }));
        test("§4.8  negative idx throws",              throws([&]{ l5.add_idx(5,-1); }));

        SingleLinkedList l6 = make({1});
        l6.add_idx(2, 1);
        test("§4.9  on single elem: get(1)==2",        l6.get(1) == 2);
        test("§4.10 on single elem: circular",         l6.tail->next == l6.head);
    }

    // ─────────────────────────────────────────
    // §5. delete_front
    // ─────────────────────────────────────────
    {
        SingleLinkedList l = make({1,2,3});
        l.delete_front();
        test("§5.1  removes head: get(0)==2",          l.get(0) == 2);
        test("§5.2  size decreases: size==2",          l.size == 2);
        test("§5.3  circular maintained",              l.tail->next == l.head);

        l.delete_front();
        test("§5.4  second delete: head==3",           l.head->data == 3);
        test("§5.5  second delete: tail==3",           l.tail->data == 3);

        l.delete_front();
        test("§5.6  last delete: is_empty",            l.is_empty());
        test("§5.7  last delete: head==nullptr",       l.head == nullptr);
        test("§5.8  last delete: tail==nullptr",       l.tail == nullptr);

        test("§5.9  throws on empty",                  throws([&]{ l.delete_front(); }));

        SingleLinkedList l2 = make({10,20,30,40,50});
        l2.delete_front(); l2.delete_front();
        test("§5.10 x2 delete: size==3",               l2.size == 3);
        test("§5.11 x2 delete: head==30",              l2.head->data == 30);
        test("§5.12 x2 delete: tail==50",              l2.tail->data == 50);
        test("§5.13 x2 delete: circular",              l2.tail->next == l2.head);
    }

    // ─────────────────────────────────────────
    // §6. delete_back
    // ─────────────────────────────────────────
    {
        SingleLinkedList l = make({1,2,3});
        l.delete_back();
        test("§6.1  tail==2",                          l.tail->data == 2);
        test("§6.2  size==2",                          l.size == 2);
        test("§6.3  circular",                         l.tail->next == l.head);

        l.delete_back();
        test("§6.4  x2: size==1",                     l.size == 1);
        test("§6.5  x2: head==tail",                   l.head == l.tail);

        l.delete_back();
        test("§6.6  last: is_empty",                   l.is_empty());
        test("§6.7  throws on empty",                  throws([&]{ l.delete_back(); }));

        SingleLinkedList l2 = make({1,2,3,4,5});
        l2.delete_back(); l2.delete_back();
        test("§6.8  x2: tail==3",                     l2.tail->data == 3);
        test("§6.9  x2: size==3",                     l2.size == 3);
        test("§6.10 x2: circular",                    l2.tail->next == l2.head);
    }

    // ─────────────────────────────────────────
    // §7. delete_idx
    // ─────────────────────────────────────────
    {
        SingleLinkedList l = make({1,2,3});
        l.delete_idx(1);
        test("§7.1  middle: get(0)==1",                l.get(0) == 1);
        test("§7.2  middle: get(1)==3",                l.get(1) == 3);
        test("§7.3  middle: size==2",                  l.size == 2);
        test("§7.4  middle: circular",                 l.tail->next == l.head);

        SingleLinkedList l2 = make({1,2,3});
        l2.delete_idx(0);
        test("§7.5  front: head==2",                   l2.head->data == 2);

        SingleLinkedList l3 = make({1,2,3});
        l3.delete_idx(2);
        test("§7.6  back: tail==2",                    l3.tail->data == 2);

        SingleLinkedList l4 = make({42});
        l4.delete_idx(0);
        test("§7.7  only elem: is_empty",              l4.is_empty());

        SingleLinkedList l5; l5.init();
        test("§7.8  empty throws",                     throws([&]{ l5.delete_idx(0); }));

        SingleLinkedList l6 = make({1,2});
        test("§7.9  out-of-range throws",              throws([&]{ l6.delete_idx(5); }));
        test("§7.10 negative idx throws",              throws([&]{ l6.delete_idx(-1); }));
    }

    // ─────────────────────────────────────────
    // §8. get
    // ─────────────────────────────────────────
    {
        SingleLinkedList l = make({10,20,30});
        test("§8.1  get(0)==10",                       l.get(0) == 10);
        test("§8.2  get(1)==20",                       l.get(1) == 20);
        test("§8.3  get(2)==30",                       l.get(2) == 30);

        SingleLinkedList l2; l2.init();
        test("§8.4  empty throws",                     throws([&]{ l2.get(0); }));
        test("§8.5  out-of-range throws",              throws([&]{ l.get(5); }));
        test("§8.6  negative idx throws",              throws([&]{ l.get(-1); }));

        SingleLinkedList l3 = make({99});
        test("§8.7  single element",                   l3.get(0) == 99);

        SingleLinkedList l4; l4.init();
        for (int i = 0; i < 10; i++) l4.add_back(i * 3);
        bool ok = true;
        for (int i = 0; i < 10; i++) ok &= (l4.get(i) == i * 3);
        test("§8.8  sequential get x10",               ok);

        SingleLinkedList l5 = make({-1,-2,-3});
        test("§8.9  negative stored value",            l5.get(2) == -3);

        SingleLinkedList l6 = make({1,2,3,4});
        l6.delete_front();
        test("§8.10 get after delete_front",           l6.get(0) == 2);
    }

    // ─────────────────────────────────────────
    // §9. set
    // ─────────────────────────────────────────
    {
        SingleLinkedList l = make({1,2,3});
        l.set(99, 0);
        test("§9.1  set first: get(0)==99",            l.get(0) == 99);
        l.set(88, 1);
        test("§9.2  set middle: get(1)==88",           l.get(1) == 88);
        l.set(77, 2);
        test("§9.3  set last: get(2)==77",             l.get(2) == 77);

        SingleLinkedList l2; l2.init();
        test("§9.4  empty throws",                     throws([&]{ l2.set(1, 0); }));
        test("§9.5  out-of-range throws",              throws([&]{ l.set(99, 10); }));
    }

    // ─────────────────────────────────────────
    // §10. clear
    // ─────────────────────────────────────────
    {
        SingleLinkedList l = make({1,2,3,4,5});
        l.clear();
        test("§10.1 is_empty after clear",             l.is_empty());
        test("§10.2 size==0 after clear",              l.size == 0);
        test("§10.3 head==nullptr after clear",        l.head == nullptr);
        test("§10.4 tail==nullptr after clear",        l.tail == nullptr);

        SingleLinkedList l2; l2.init();
        l2.clear(); // should not crash
        test("§10.5 clear on empty: no crash",         true);
    }

    // Summary
    std::cout << "\n=== " << g_passed << " / " << (g_passed + g_failed)
              << " tests passed ===\n";
    return (g_failed == 0) ? 0 : 1;
}