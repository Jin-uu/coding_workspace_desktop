#include <iostream>
#include <queue>
#define MAX_N 100

using namespace std;

typedef struct _loc{
    int a;
    int b;
    int c;
} loc;

int m,n,h,togo;
int box[MAX_N+1][MAX_N+1][MAX_N+1];
queue<loc> q;
int move_m[] = {0, 0, -1, 1, 0, 0};
int move_n[] = {0, 0, 0, 0, -1, 1};
int move_h[] = {1, -1, 0, 0, 0, 0};

bool isPosLoc(int ia, int ib, int ic){
    if(ia < 0 || ib < 0 || ic < 0 || ia >= m || ib >=n || ic >= h) return false;
    return true;
}

int solve(){
    int cm, cn, ch, nm, nn, nh,len, day=0;
    while(!q.empty()){
        if(togo <= 0) return day;
        day++; len = q.size();
        for (int i = 0; i < len; i++) {
            cm = q.front().a; cn = q.front().b; ch = q.front().c; q.pop();
            for (int mov = 0; mov < 6; mov++) {
                nm = cm + move_m[mov]; nn = cn + move_n[mov]; nh = ch + move_h[mov];
                if(!isPosLoc(nm, nn, nh)) continue;
                if(box[nh][nn][nm] == 0){
                    q.push({nm,nn,nh});
                    box[nh][nn][nm] = 1;
                    togo--;
                }
            }            
        }   
    }
    return -1;
}

int main(void){
    cin >> m >> n >> h;

    for (int i = 0; i < h; i++) for (int j = 0; j < n; j++) for (int k = 0; k < m; k++) {
        cin >> box[i][j][k];
        if(box[i][j][k] == 1) q.push({k,j,i});
        if(box[i][j][k] == 0) togo++;
    }
    cout << solve() << endl;
}