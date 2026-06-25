#include <iostream>
#include <utility>
#include "double_linked_list.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, r;
    if (!(cin >> n >> r)) return 0;

    DoubleLinkedList list;
    list.init();

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        list.add_back(c);
    }

    if (list.size == 0) {
        cout << "EMPTY\n";
        return 0;
    }

    Node* alpha = list.head;
    Node* beta = list.tail;

    for (int i = 0; i < r; i++) {
        long long x, y;
        cin >> x >> y;

        if (list.size == 0) continue;

        long long moves_alpha = x % list.size;
        if (moves_alpha > list.size / 2) {
            long long back_moves = list.size - moves_alpha;
            for (long long j = 0; j < back_moves; j++) alpha = alpha->prev;
        } else {
            for (long long j = 0; j < moves_alpha; j++) alpha = alpha->next;
        }

        long long moves_beta = y % list.size;
        if (moves_beta > list.size / 2) {
            long long forward_moves = list.size - moves_beta;
            for (long long j = 0; j < forward_moves; j++) beta = beta->next;
        } else {
            for (long long j = 0; j < moves_beta; j++) beta = beta->prev;
        }

        if (alpha == beta) {
            Node* target = alpha;
            
            if (list.size == 1) {
                list.head = nullptr;
                list.tail = nullptr;
                alpha = nullptr;
                beta = nullptr;
            } else {
                Node* next_a = target->next;
                Node* next_b = target->prev;
                
                target->prev->next = target->next;
                target->next->prev = target->prev;
                
                if (target == list.head) list.head = target->next;
                if (target == list.tail) list.tail = target->prev;
                
                alpha = next_a;
                beta = next_b;
            }
            
            delete target;
            list.size--;
            
        } else {
            bool is_adjacent = false;
            
            if (alpha->next == beta && alpha != list.tail) is_adjacent = true;
            if (beta->next == alpha && beta != list.tail) is_adjacent = true;
            
            if (is_adjacent) {
                swap(alpha->data, beta->data);
            }
        }
    }

    if (list.size == 0) {
        cout << "EMPTY\n";
    } else {
        Node* curr = list.head;
        for (int i = 0; i < list.size; i++) {
            cout << curr->data;
            curr = curr->next;
        }
        cout << "\n";
    }

    list.clear();

    return 0;
}