#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#define MAX_N 20'000
#define MAX_E 200'000
#define RED 1
#define BLUE 2
using namespace std;

int t, n, e, tfrom, tto;
int color[MAX_N+1];

void bfs(int curr){

}

bool solve(){
    vector<int> edge[MAX_N+1]; queue<int> q;
    memset(color, -1, sizeof(color));
    
    cin >> n >> e;
    for (int i = 0; i < e; i++) {
        cin >> tfrom >> tto;
        edge[tfrom].push_back(tto);
        edge[tto].push_back(tfrom);
    }

    for (int i = 1; i <= n; i++) {
        if(color[i] != -1) continue;
        q.push(i);
        color[i] = RED;

        int cn, nn;
        while(!q.empty()){
            cn = q.front(); q.pop();
            for (int i = 0; i < edge[cn].size(); i++) {
                nn = edge[cn][i];
                if(color[nn] != -1) {
                    if(color[nn] == color[cn]) return false;
                    continue;
                }
                q.push(nn); color[nn] = !color[cn];
            }
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> t;
    for (int i = 0; i < t; i++) {
        if(solve()) {
            cout << "YES" << '\n';
            continue;
        }
        cout << "NO" << '\n';
    }
}