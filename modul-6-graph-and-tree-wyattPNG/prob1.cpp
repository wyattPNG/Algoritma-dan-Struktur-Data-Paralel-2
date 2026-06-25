#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<char> labels(N);
    map<char, int> idx;
    for (int i = 0; i < N; i++) {
        cin >> labels[i];
        idx[labels[i]] = i;
    }

    vector<vector<int>> matrix(N, vector<int>(N, 0));

    int M;
    cin >> M;
    for (int i = 0; i < M; i++) {
        char u, v; int w;
        cin >> u >> v >> w;
        matrix[idx[u]][idx[v]] = w;
    }

    cout << "Adjacency Matrix:" << endl;
    cout << " ";
    for (int i = 0; i < N; i++) cout << " " << labels[i];
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << labels[i];
        for (int j = 0; j < N; j++) cout << " " << matrix[i][j];
        cout << endl;
    }
    return 0;
}