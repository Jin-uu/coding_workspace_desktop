#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef struct _path{
    int from;
    int to;
} path;
typedef struct _loc{
    int curr;
    int depth;
} loc;

int n, m;
bool isChk[100+1];
vector<path> ld, snk;
queue<loc> q;

int getNext(int loc){
    for (int i = 0; i < n; i++) if(loc == ld[i].from) return ld[i].to;
    for (int i = 0; i < m; i++) if(loc == snk[i].from) return snk[i].to;
    return loc;
}

int solve(){
    int cl, nl, cdep;
    q.push({1,0});
    isChk[1] = true;
    while(!q.empty()){
        cl = q.front().curr; cdep = q.front().depth; q.pop();
        if(cl == 100) return cdep;
        for (int i = 1; i <= 6; i++) {
            nl = getNext(cl+i);
            if(isChk[nl]) continue;
            q.push({nl,cdep+1});
            isChk[nl] = true;
        }
    }
    return -1;
}

int main(void){
    cin >> n >> m;
    path temp;
    for (int i = 0; i < n; i++) {
        cin >> temp.from >> temp.to;
        ld.push_back({temp.from, temp.to});
    }
    for (int i = 0; i < m; i++) {
        cin >> temp.from >> temp.to;
        snk.push_back({temp.from, temp.to});
    }
    cout << solve();
}