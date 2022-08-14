#include <iostream>
#include <queue>
#define MAX_N 100'000
using namespace std;
typedef struct _loc {
    int n;
    int depth;
} loc;
int n,k;
bool isChk[MAX_N+1];
queue<loc> q;

int next_x(int x, int type){
    if(type == 0) return x-1;
    if(type == 1) return x+1;
    if(type == 2) return x*2;
    return -1;
}

int solve(){
    q.push({n,0}); isChk[n] = true;
    int cx, cdep, nx;
    while(!q.empty()){
        cx = q.front().n; cdep = q.front().depth; q.pop();
        if(cx == k) return cdep;
        for (int i = 0; i < 3; i++) {
            nx = next_x(cx, i);
            if(nx < 0 || nx > MAX_N) continue;
            if(isChk[nx]) continue;
            q.push({nx, cdep+1}); isChk[nx] = true;
        }
    }
    return -1;
}

int main(void){
    cin >> n >> k; cout << solve();
}