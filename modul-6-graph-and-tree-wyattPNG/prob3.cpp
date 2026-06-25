#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int R, C;
    cin >> R >> C;
    vector<vector<int> > grid(R, vector<int>(C));
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            cin >> grid[i][j];

    int SR, SC, FR, FC;
    cin >> SR >> SC >> FR >> FC;

    if (SR == FR && SC == FC) { cout << 0 << endl; return 0; }

    vector<vector<int> > dist(R, vector<int>(C, -1));
    queue<pair<int,int> > q;
    dist[SR][SC] = 0;
    q.push(make_pair(SR, SC));

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] == 0 && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                if (nr == FR && nc == FC) { cout << dist[nr][nc] << endl; return 0; }
                q.push(make_pair(nr, nc));
            }
        }
    }

    cout << -1 << endl;
    return 0;
}