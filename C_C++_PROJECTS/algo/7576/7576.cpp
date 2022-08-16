#include <iostream>
#include <queue>
#define MAX_N 1000

using namespace std;

typedef struct _loc{
    int m;
    int n;
} loc;

int m,n,togo;
int box[MAX_N+1][MAX_N+1];
queue<loc> q;
int move_m[] = {-1, 1, 0, 0};
int move_n[] = { 0, 0, -1, 1};

bool isPosLoc(int im, int in){
    if(im < 0 || in < 0 || im >= m || in >=n) return false;
    return true;
}

int solve(){
    int cm, cn, nm, nn, len, day=0;
    while(!q.empty()){
        if(togo <= 0) return day;
        day++; len = q.size();
        for (int i = 0; i < len; i++) {
            cm = q.front().m; cn = q.front().n; q.pop();
            for (int mov = 0; mov < 4; mov++) {
                nm = cm + move_m[mov]; nn = cn + move_n[mov];
                if(!isPosLoc(nm, nn)) continue;
                if(box[nn][nm] == 0){
                    q.push({nm,nn});
                    box[nn][nm] = 1;
                    togo--;
                }
            }            
        }   
    }
    return -1;
}

int main(void){
    cin >> m >> n;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        cin >> box[i][j];
        if(box[i][j] == 1) q.push({j,i});
        if(box[i][j] == 0) togo++;
    }
    cout << solve() << endl;
}