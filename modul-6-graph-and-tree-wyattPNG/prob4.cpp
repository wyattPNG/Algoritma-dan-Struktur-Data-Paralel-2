#include <iostream>
#include <vector>
using namespace std;

int R, C, FR, FC, count_path;
vector<vector<int>> grid;
vector<vector<bool>> visited;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void dfs(int r, int c) {
    if (r == FR && c == FC) { count_path++; return; }
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] == 0 && !visited[nr][nc]) {
            visited[nr][nc] = true;
            dfs(nr, nc);
            visited[nr][nc] = false;
        }
    }
}

int main() {
    cin >> R >> C;
    grid.assign(R, vector<int>(C));
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            cin >> grid[i][j];

    int SR, SC;
    cin >> SR >> SC >> FR >> FC;

    count_path = 0;
    visited.assign(R, vector<bool>(C, false));
    visited[SR][SC] = true;
    dfs(SR, SC);

    cout << count_path << endl;
    return 0;
}