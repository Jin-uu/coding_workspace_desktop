#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <queue>
#include <cmath>
#include <cstring>
#define MAX_N 8

using namespace std;
typedef struct _loc {
    int r;
    int c;
} loc;

bool isChk[MAX_N * MAX_N +1];
int n, m, ans=0;
int MAP[MAX_N+1][MAX_N+1];
int isVis[MAX_N+1][MAX_N+1];
int move_r[] = {-1, 1, 0, 0};
int move_c[] = {0, 0, -1, 1};
vector<loc> vrs, mt;
vector<int> sels;

int get_mt_num(void){
    int cnt = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if(MAP[i][j] == 0) cnt++;
    return cnt;    
}

int bfs(int ir, int ic){
    int cnt=0;
    queue<loc> q;
    q.push({ir,ic}); isVis[ir][ic] = true;

    int cr, cc, nr, nc;
    while(!q.empty()){
        cr = q.front().r; cc = q.front().c; q.pop();
        // auto [cr, cc] = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            nr = cr + move_r[i]; nc = cc + move_c[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            if(MAP[nr][nc] != 0) continue;
            if(isVis[nr][nc]) continue;
            q.push({nr,nc}); isVis[nr][nc] = true; cnt++;
        }
    }
    return cnt;
}

void dfs(){
    if(sels.size() == 3){
        memset(isVis, false, sizeof(isVis));
        int cnt=0, jin;
        for (int i = 0; i < 3; i++) {
            MAP[mt[sels[i]].r][mt[sels[i]].c] = 1;   
        }
        for (int i = 0; i < vrs.size(); i++) {
            cnt += bfs(vrs[i].r, vrs[i].c);
        }
        jin = mt.size() - 3 - cnt;
        ans = max(ans, jin);
        for (int i = 0; i < 3; i++) {
            MAP[mt[sels[i]].r][mt[sels[i]].c] = 0;   
        }
        return;
    }

    for (int i = 0; i < mt.size(); i++){
        if(isChk[i]) continue;
        sels.push_back(i);
        isChk[i] = true;
        dfs();
        sels.pop_back();
        isChk[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> MAP[i][j];
            if(MAP[i][j] == 0) mt.push_back({i,j});
            if(MAP[i][j] == 2) vrs.push_back({i,j});
        }
    }

    dfs();
    cout << ans;





}