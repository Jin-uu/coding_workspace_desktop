#include <iostream>
#include <queue>
#include <cstring>
#define MAX_N 50
using namespace std;

int t, m, n, k;
int MAP[MAX_N+1][MAX_N+1];
bool isChk[MAX_N+1][MAX_N+1];
int move_r[] = {-1, 1, 0, 0};
int move_c[] = {0, 0, -1, 1};
queue<pair<int,int>> q;

void bfs(int r, int c){
    q.push({r,c}); isChk[r][c] = true;
    int cr, cc, nr, nc;
    while (!q.empty()) {
        cr = q.front().first; cc = q.front().second; q.pop();
        for (int mov = 0; mov < 4; mov++) {
            nr = cr + move_r[mov]; nc = cc + move_c[mov];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            if(isChk[nr][nc] || MAP[nr][nc] == 0) continue;
            q.push({nr,nc}); isChk[nr][nc] = true;
        }
    }
}

int solve(void){
    memset(MAP, 0, sizeof(MAP)); memset(isChk, false, sizeof(isChk));
    cin >> m >> n >> k;
    int temp_r, temp_c, ans=0;
    for (int i = 0; i < k; i++) {
        cin >> temp_c >> temp_r; MAP[temp_r][temp_c] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(isChk[i][j] || MAP[i][j]==0) continue;
            bfs(i,j); ans++;
        }
    }
    return ans;
}

int main(void){
    cin >> t;
    for (int tc = 0; tc < t; tc++) {
        cout << solve() << '\n';
    }
}