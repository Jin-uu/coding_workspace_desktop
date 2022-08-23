#include <iostream>
#include <algorithm>
#include <queue>
#define MAX_N 1'000'000
typedef struct _num{
    int curr;
    int depth;
} num;
using namespace std;

int x;
int track[MAX_N+1];
int get_next(int curr, int mov){
    if(mov == 0){
        if(curr % 3 == 0) return curr/3;
        return -1;
    }
    if(mov == 1){
        if(curr % 2 == 0) return curr/2;
        return -1;        
    }
    if(mov == 2) return curr-1;       

    return -1;
}

int bfs(int fst){
    queue<num> q;
    q.push({fst, 0});
    track[fst] = fst;

    int cn, cdep, nn;
    while(!q.empty()){
        cn = q.front().curr; cdep = q.front().depth; q.pop();
        if(cn == 1) return cdep;

        for (int mov = 0; mov < 3; mov++) {
            nn = get_next(cn, mov);
            if(nn == -1) continue;
            if(track[nn] != 0) continue;
            q.push({nn,cdep+1}); track[nn] = cn;            
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> x;
    cout << bfs(x) << '\n';
    int t=1;
    vector<int> trk;
    while(t!=x){
        trk.push_back(t);
        t = track[t];
    }
    trk.push_back(x);
    for (int i = trk.size()-1; i >= 0; i--) {
        cout << trk[i] << " ";
    }
    
}