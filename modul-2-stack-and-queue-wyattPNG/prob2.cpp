#include <iostream>
#include "queue.h"

using namespace std;

int main() {
    int n, k;
    
    if (!(cin >> n >> k)) return 0;

    if (k <= 0) return 0;

    Queue q;
    init(&q);

    int current_sum = 0;

    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;

        if (i < k) {
            enqueue(&q, val);
            current_sum += val;
            
            if (i == k - 1) {
                cout << current_sum;
            }
        } else {
            current_sum -= front(&q);
            dequeue(&q);
            
            enqueue(&q, val);
            current_sum += val;
            
            cout << " " << current_sum;
        }
    }
    
    cout << endl;

    return 0;
}