#include <iostream>
#include "single_linked_list.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    int k;
    
    if (!(cin >> n >> k)) return 0;
    
    SingleLinkedList list;
    list.init();
    
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        list.add_back(val);
    }
    
    int initial_k = k;
    int current_k = k;
    
    Node* curr = list.head;
    Node* prev = list.tail; 
    
    while (list.size > 1) {
        int steps = (current_k - 1) % list.size;
        
        for (int i = 0; i < steps; i++) {
            prev = curr;
            curr = curr->next;
        }
        
        int destroyed_val = curr->data;
        
        prev->next = curr->next;
        if (curr == list.head) list.head = curr->next;
        if (curr == list.tail) list.tail = prev;
        
        Node* target = curr;
        curr = curr->next;
        delete target;
        list.size--;
        
        if (destroyed_val % 2 == 0) {
            current_k++;
        } else {
            current_k--;
        }
        
        if (current_k <= 0) {
            current_k = initial_k;
        }
    }
    
    if (list.size == 1) {
        cout << list.head->data << "\n";
    }
    
    list.clear();
    
    return 0;
}