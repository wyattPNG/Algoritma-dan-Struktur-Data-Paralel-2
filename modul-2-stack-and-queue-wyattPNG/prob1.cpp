#include <iostream>
#include <string>
#include "stack.h" 

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    Stack s;
    init(&s);

    for (int i = 0; i < n; ++i) {
        string token;
        cin >> token;

        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = peek(&s);
            pop(&s);
            
            int a = peek(&s);
            pop(&s);

            int result = 0;
            if (token == "+") {
                result = a + b;
            } else if (token == "-") {
                result = a - b;
            } else if (token == "*") {
                result = a * b;
            } else if (token == "/") {
                result = a / b;
            }

            push(&s, result);
        } else {
            int nilai = stoi(token);
            push(&s, nilai);
        }
    }

    cout << peek(&s) << endl;

    return 0;
}