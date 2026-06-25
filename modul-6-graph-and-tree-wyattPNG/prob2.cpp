#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<char> labels(N);
    for (int i = 0; i < N; i++) cin >> labels[i];

    vector<vector<int>> matrix(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> matrix[i][j];

    cout << "Adjacency List:" << endl;
    for (int i = 0; i < N; i++) {
        cout << labels[i] << " -> ";
        bool hasEdge = false;
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] > 0) {
                if (hasEdge) cout << ", ";
                cout << "(" << labels[j] << "," << matrix[i][j] << ")";
                hasEdge = true;
            }
        }
        if (!hasEdge) cout << "-";
        cout << endl;
    }
    return 0;
}