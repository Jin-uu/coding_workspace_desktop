#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#define MAX_N 50
using namespace std;
typedef struct _loc{
    int r;
    int c;
} loc;
int t, m, n, k;
int MAP[MAX_N+1][MAX_N+1];
bool isVis[MAX_N+1][MAX_N+1];
int move_r[] = {-1, 1, 0, 0};
int move_c[] = {0, 0, -1, 1};

void bfs(int ir, int ic){
    queue<loc> q;
    q.push({ir,ic});
    isVis[ir][ic] = true;
    int cr, cc, nr, nc;
    while(!q.empty()){
        cr = q.front().r; cc = q.front().c; q.pop();
        for (int mov = 0; mov < 4; mov++) {
            nr = cr + move_r[mov]; nc = cc + move_c[mov];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            if(MAP[nr][nc] != 1) continue;
            if(isVis[nr][nc]) continue;
            q.push({nr,nc}); isVis[nr][nc] = true;
        }
    }
}

int solve(){
    memset(isVis, false, sizeof(isVis));
    int ans=0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(MAP[i][j] != 1) continue;
            if(isVis[i][j]) continue;
            bfs(i,j); ans++;
        }
    }
    return ans;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int temp_r, temp_c;
    cin >> t;
    for (int i = 0; i < t; i++) {
        memset(MAP, 0, sizeof(MAP));
        cin >> n >> m >> k;
        for (int i = 0; i < k; i++){
            cin >> temp_r >> temp_c;
            MAP[temp_r][temp_c] = 1;
        }
        cout << solve() << '\n';
    }
}