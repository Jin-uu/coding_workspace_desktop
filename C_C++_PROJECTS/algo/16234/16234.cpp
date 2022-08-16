#include <iostream>
#include <cstring>
#include <queue>
#define MAX_N 50
typedef struct _loc{
    int r;
    int c;
} loc;

using namespace std;

int n,lt,rt;
int MAP[MAX_N+1][MAX_N+1];
int isVis[MAX_N+1][MAX_N+1];
int move_r[] = {-1, 1, 0, 0};
int move_c[] = {0, 0, -1, 1};

bool isPosLoc(int ir, int ic){
    if(ir < 0 || ic < 0 || ir >= n || ic >=n) return false;
    return true;
}

bool isStable(){
    int nr,nc,diff;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int mov = 0; mov < 4; mov++) {
                nr = i+move_r[mov]; nc = j+move_c[mov];
                if(isPosLoc(nr,nc)){
                    diff = abs(MAP[i][j] - MAP[nr][nc]);
                    if(diff >= lt && diff <= rt) return false;
                }
            }   
        }
    }
    return true;
}

void bfs(int r, int c){
    queue<loc> q;
    vector<loc> v;
    q.push({r,c});
    isVis[r][c] = true;

    int cr, cc, nr, nc, total=0, diff;
    while(!q.empty()){
        cr = q.front().r; cc = q.front().c; q.pop();
        total += MAP[cr][cc];
        v.push_back({cr,cc});
        for (int mov = 0; mov < 4; mov++) {
            nr = cr + move_r[mov]; nc = cc + move_c[mov];
            if(!isPosLoc(nr,nc)) continue;
            if(isVis[nr][nc]) continue;
            diff = abs(MAP[nr][nc] - MAP[cr][cc]);
            if(diff < lt || diff > rt) continue;
            q.push({nr,nc}); isVis[nr][nc] = true;
        }
    }
    for (int i = 0; i < v.size(); i++)
        MAP[v[i].r][v[i].c] = total / v.size();
}

void __dbg_print_MAP(){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << MAP[i][j] << " ";
        }
        cout << endl;        
    }    
}

int solve(){
    int day=0;
    while(!isStable()){
        day++;
        memset(isVis, false, sizeof(isVis));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(isVis[i][j]) continue;
                bfs(i,j);
            }            
        }
    }

    return day;
}

int main(void){
    cin >> n >> lt >> rt;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> MAP[i][j];
    cout << solve();
}