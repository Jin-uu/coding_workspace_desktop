#include <iostream>
#include <queue>
#include <cstring>
#include <limits.h>
#define MAX_N 20
#define INF INT_MAX
using namespace std;

typedef struct _loc{
    int r;
    int c;
}loc;

int n, cr, cc, siz=2, etn=0;
int map[MAX_N+1][MAX_N+1];
int move_r[] = {-1, 0, 0, 1};
int move_c[] = {0, -1, 1, 0};
bool isChk[MAX_N+1][MAX_N+1];

bool isPosLoc(int ir, int ic){
    if(ir < 0 || ic < 0 || ir >= n || ic >= n) return false;
    return true;
}

bool isEtble(int ir, int ic){
    int tgt = map[ir][ic];
    if(tgt != 9 && tgt < siz) return true;
    return false;
}

int bfs(int r, int c){
    queue<loc> q;
    int nr, nc, er=INF, ec=INF, time=0, qlen;
    memset(isChk, false, sizeof(isChk));
    q.push({r,c});
    isChk[r][c] = true;
    while (!q.empty()){
        time++;
        qlen = q.size();
        for (int i = 0; i < qlen; i++) {
            cr = q.front().r; cc = q.front().c; q.pop();
            for (int mov = 0; mov < 4; mov++) {
                nr = cr + move_r[mov]; nc = cc + move_c[mov];
                if(!isPosLoc(nr, nc)) continue;
                if(map[nr][nc] == 0 || map[nr][nc] == siz){
                    if(isChk[nr][nc]) continue;
                    q.push({nr,nc});
                    isChk[nr][nc] = true;
                    continue;
                }
                if(isEtble(nr, nc)){
                    if(nr < er){
                        er = nr; ec = nc; continue;
                    }
                    if(nr == er) {
                        if(nc < ec) {
                            er = nr; ec = nc; continue;
                        }
                    }        
                }
            }
        }
        if(er != INF){
            map[er][ec] = 0; cr = er; cc = ec; etn++;
            return time;
        }
    }
    return -1;
}

int solve(void){
    int dist,ans=0;
    while((dist = bfs(cr,cc)) != -1){
        ans += dist;
        if(etn >= siz){
            siz++; etn = 0;
        }
    }
    return ans;
}

int main(void){
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
            if(map[i][j] == 9){
                cr = i; cc = j;
                map[i][j] = 0;
            }
        }    
    cout << solve();
}