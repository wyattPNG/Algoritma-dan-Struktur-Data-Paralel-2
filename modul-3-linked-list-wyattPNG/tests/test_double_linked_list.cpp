// tests/test_double_linked_list.cpp
// Exhaustive unit tests for DoubleLinkedList (non-circular, bidirectional)
// exit 0 = all pass, exit 1 = any failure

#include "../double_linked_list.h"
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

static DoubleLinkedList make(std::initializer_list<int> vals) {
    DoubleLinkedList l;
    l.init();
    for (int v : vals) l.add_back(v);
    return l;
}

int main() {
    std::cout << "=== Double Linked List Unit Tests ===\n\n";

    // ─────────────────────────────────────────
    // §1. init & is_empty
    // ─────────────────────────────────────────
    {
        DoubleLinkedList l; l.init();
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
        DoubleLinkedList l; l.init();
        l.add_front(42);
        test("§2.1  single: get(0)==42",             l.get(0) == 42);
        test("§2.2  single: size==1",                l.size == 1);
        test("§2.3  single: head==tail",             l.head == l.tail);
        test("§2.4  single: head->prev==nullptr",    l.head->prev == nullptr);
        test("§2.5  single: tail->next==nullptr",    l.tail->next == nullptr);

        l.add_front(99);
        test("§2.6  two: get(0)==99",                l.get(0) == 99);
        test("§2.7  two: get(1)==42",                l.get(1) == 42);
        test("§2.8  two: head->prev==nullptr",       l.head->prev == nullptr);
        test("§2.9  two: tail->next==nullptr",       l.tail->next == nullptr);
        test("§2.10 two: head->next->prev==head",    l.head->next->prev == l.head);

        l.add_front(1);
        test("§2.11 three: get(0)==1",               l.get(0) == 1);
        test("§2.12 three: order 1,99,42",           l.get(1)==99 && l.get(2)==42);
        test("§2.13 three: size==3",                 l.size == 3);

        DoubleLinkedList l2; l2.init();
        l2.add_front(-7);
        test("§2.14 negative value",                 l2.get(0) == -7);

        DoubleLinkedList l3; l3.init();
        for (int i = 0; i < 10; i++) l3.add_front(i);
        test("§2.15 x10: size==10",                  l3.size == 10);
    }

    // ─────────────────────────────────────────
    // §3. add_back
    // ─────────────────────────────────────────
    {
        DoubleLinkedList l; l.init();
        l.add_back(7);
        test("§3.1  single: get(0)==7",              l.get(0) == 7);
        test("§3.2  single: size==1",                l.size == 1);
        test("§3.3  single: head==tail",             l.head == l.tail);
        test("§3.4  single: tail->next==nullptr",    l.tail->next == nullptr);

        l.add_back(8);
        test("§3.5  two: get(0)==7 get(1)==8",       l.get(0)==7 && l.get(1)==8);
        test("§3.6  two: tail->data==8",             l.tail->data == 8);
        test("§3.7  two: tail->next==nullptr",       l.tail->next == nullptr);
        test("§3.8  two: head->prev==nullptr",       l.head->prev == nullptr);
        test("§3.9  two: tail->prev->data==7",       l.tail->prev->data == 7);

        DoubleLinkedList l2; l2.init();
        l2.add_back(1); l2.add_back(2); l2.add_back(3);
        test("§3.10 bidi forward: head->next->data==2",  l2.head->next->data == 2);
        test("§3.11 bidi backward: tail->prev->data==2", l2.tail->prev->data == 2);

        DoubleLinkedList l3; l3.init();
        l3.add_front(2); l3.add_back(3); l3.add_front(1);
        test("§3.12 mixed: get(0)==1",               l3.get(0) == 1);
        test("§3.13 mixed: get(1)==2",               l3.get(1) == 2);
        test("§3.14 mixed: get(2)==3",               l3.get(2) == 3);

        DoubleLinkedList l4; l4.init();
        for (int i = 0; i < 5; i++) l4.add_back(i * 10);
        test("§3.15 seq x5: size==5",                l4.size == 5);
    }

    // ─────────────────────────────────────────
    // §4. add_idx
    // ─────────────────────────────────────────
    {
        DoubleLinkedList l = make({2,3});
        l.add_idx(1, 0);
        test("§4.1  at front: get(0)==1",            l.get(0) == 1);

        DoubleLinkedList l2 = make({1,2});
        l2.add_idx(3, 2);
        test("§4.2  at back: get(2)==3",             l2.get(2) == 3);

        DoubleLinkedList l3 = make({1,3});
        l3.add_idx(2, 1);
        test("§4.3  at middle: get(1)==2",           l3.get(1) == 2);
        test("§4.4  at middle: size==3",             l3.size == 3);
        test("§4.5  at middle: prev link correct",   l3.head->next->next->prev->data == 2);
        test("§4.6  at middle: next link correct",   l3.head->next->next->data == 3);

        DoubleLinkedList l4 = make({1,2,4,5});
        l4.add_idx(3, 2);
        bool seq = true;
        for (int i = 0; i < 5; i++) seq &= (l4.get(i) == i+1);
        test("§4.7  order after insert correct",     seq);

        // DLL silently ignores out-of-range (returns void, no throw)
        DoubleLinkedList l5 = make({1,2});
        l5.add_idx(5, 10);
        test("§4.8  out-of-range: silent, size==2",  l5.size == 2);
        l5.add_idx(5, -1);
        test("§4.9  negative idx: silent, size==2",  l5.size == 2);

        DoubleLinkedList l6 = make({1});
        l6.add_idx(2, 1);
        test("§4.10 on single: get(1)==2",           l6.get(1) == 2);
    }

    // ─────────────────────────────────────────
    // §5. delete_front
    // ─────────────────────────────────────────
    {
        DoubleLinkedList l = make({1,2,3});
        l.delete_front();
        test("§5.1  removes head: get(0)==2",        l.get(0) == 2);
        test("§5.2  size decreases: size==2",        l.size == 2);
        test("§5.3  new head->prev==nullptr",        l.head->prev == nullptr);
        test("§5.4  tail unchanged: tail->data==3",  l.tail->data == 3);

        l.delete_front(); l.delete_front();
        test("§5.5  delete all: is_empty",           l.is_empty());
        test("§5.6  delete all: head==nullptr",      l.head == nullptr);
        test("§5.7  delete all: tail==nullptr",      l.tail == nullptr);

        // DLL silently ignores delete on empty
        DoubleLinkedList l2; l2.init();
        l2.delete_front();
        test("§5.8  empty: silent (no crash)",       true);

        DoubleLinkedList l3 = make({10,20,30,40,50});
        l3.delete_front(); l3.delete_front();
        test("§5.9  x2: size==3",                   l3.size == 3);
        test("§5.10 x2: head==30",                  l3.head->data == 30);
    }

    // ─────────────────────────────────────────
    // §6. delete_back
    // ─────────────────────────────────────────
    {
        DoubleLinkedList l = make({1,2,3});
        l.delete_back();
        test("§6.1  tail==2",                        l.tail->data == 2);
        test("§6.2  size==2",                        l.size == 2);
        test("§6.3  new tail->next==nullptr",        l.tail->next == nullptr);
        test("§6.4  head unchanged: head==1",        l.head->data == 1);

        l.delete_back(); l.delete_back();
        test("§6.5  delete all: is_empty",           l.is_empty());
        test("§6.6  delete all: head==nullptr",      l.head == nullptr);
        test("§6.7  delete all: tail==nullptr",      l.tail == nullptr);

        DoubleLinkedList l2; l2.init();
        l2.delete_back();
        test("§6.8  empty: silent (no crash)",       true);

        DoubleLinkedList l3 = make({1,2,3,4,5});
        l3.delete_back(); l3.delete_back();
        test("§6.9  x2: tail==3",                   l3.tail->data == 3);
        test("§6.10 x2: size==3",                   l3.size == 3);
    }

    // ─────────────────────────────────────────
    // §7. delete_idx
    // ─────────────────────────────────────────
    {
        DoubleLinkedList l = make({1,2,3});
        l.delete_idx(1);
        test("§7.1  middle: get(0)==1",              l.get(0) == 1);
        test("§7.2  middle: get(1)==3",              l.get(1) == 3);
        test("§7.3  middle: size==2",                l.size == 2);

        DoubleLinkedList l2 = make({1,2,3,4});
        l2.delete_idx(1); // remove 2, now idx0=1 idx1=3
        test("§7.4  prev link: head->next->prev->data==1", l2.head->next->prev->data == 1);

        DoubleLinkedList l3 = make({1,2,3});
        l3.delete_idx(0);
        test("§7.5  front: head==2",                 l3.head->data == 2);

        DoubleLinkedList l4 = make({1,2,3});
        l4.delete_idx(2);
        test("§7.6  back: tail==2",                  l4.tail->data == 2);

        DoubleLinkedList l5 = make({42});
        l5.delete_idx(0);
        test("§7.7  only elem: is_empty",            l5.is_empty());

        // DLL silently ignores bad idx
        DoubleLinkedList l6 = make({1,2});
        l6.delete_idx(5);
        test("§7.8  out-of-range: silent, size==2",  l6.size == 2);
        l6.delete_idx(-1);
        test("§7.9  negative: silent, size==2",      l6.size == 2);

        DoubleLinkedList l7; l7.init();
        l7.delete_idx(0);
        test("§7.10 empty: silent (no crash)",       true);
    }

    // ─────────────────────────────────────────
    // §8. get
    // ─────────────────────────────────────────
    {
        DoubleLinkedList l = make({10,20,30});
        test("§8.1  get(0)==10",                     l.get(0) == 10);
        test("§8.2  get(1)==20",                     l.get(1) == 20);
        test("§8.3  get(2)==30",                     l.get(2) == 30);

        DoubleLinkedList l2; l2.init();
        test("§8.4  empty throws",                   throws([&]{ l2.get(0); }));
        test("§8.5  out-of-range throws",            throws([&]{ l.get(5); }));
        test("§8.6  negative idx throws",            throws([&]{ l.get(-1); }));

        DoubleLinkedList l3 = make({99});
        test("§8.7  single element",                 l3.get(0) == 99);

        DoubleLinkedList l4; l4.init();
        for (int i = 0; i < 10; i++) l4.add_back(i * 3);
        bool ok = true;
        for (int i = 0; i < 10; i++) ok &= (l4.get(i) == i * 3);
        test("§8.8  sequential get x10",             ok);

        DoubleLinkedList l5 = make({-1,-2,-3});
        test("§8.9  negative stored value",          l5.get(2) == -3);

        DoubleLinkedList l6 = make({1,2,3,4});
        l6.delete_front();
        test("§8.10 get after delete_front",         l6.get(0) == 2);
    }

    // ─────────────────────────────────────────
    // §9. set
    // ─────────────────────────────────────────
    {
        DoubleLinkedList l = make({1,2,3});
        l.set(99, 0);
        test("§9.1  set first: get(0)==99",          l.get(0) == 99);
        l.set(88, 1);
        test("§9.2  set middle: get(1)==88",         l.get(1) == 88);
        l.set(77, 2);
        test("§9.3  set last: get(2)==77",           l.get(2) == 77);

        DoubleLinkedList l2; l2.init();
        test("§9.4  empty throws",                   throws([&]{ l2.set(1, 0); }));
        test("§9.5  out-of-range throws",            throws([&]{ l.set(99, 10); }));
    }

    // ─────────────────────────────────────────
    // §10. clear
    // ─────────────────────────────────────────
    {
        DoubleLinkedList l = make({1,2,3,4,5});
        l.clear();
        test("§10.1 is_empty after clear",           l.is_empty());
        test("§10.2 size==0 after clear",            l.size == 0);
        test("§10.3 head==nullptr after clear",      l.head == nullptr);
        test("§10.4 tail==nullptr after clear",      l.tail == nullptr);

        DoubleLinkedList l2; l2.init();
        l2.clear();
        test("§10.5 clear on empty: no crash",       true);
    }

    // Summary
    std::cout << "\n=== " << g_passed << " / " << (g_passed + g_failed)
              << " tests passed ===\n";
    return (g_failed == 0) ? 0 : 1;
}