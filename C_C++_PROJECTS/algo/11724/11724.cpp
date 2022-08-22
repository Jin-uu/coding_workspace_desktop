#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define MAX_N 1'000
using namespace std;
int n, m;
bool isVis[MAX_N+1];
vector<int> v[MAX_N+1];

void bfs(int s){
    queue<int> q;
    q.push(s); isVis[s] = true;
    int cx, nx;
    while(!q.empty()){
        cx = q.front(); q.pop();
        for (int i = 0; i < v[cx].size(); i++) {
            nx = v[cx][i];
            if(isVis[nx]) continue;
            q.push(nx); isVis[nx] = true;
        }        
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    int t_to, t_from, ans = 0;
    for (int i = 0; i < m; i++) {
        cin >> t_to >> t_from;
        v[t_to].push_back(t_from);
        v[t_from].push_back(t_to);
    }
    for (int i = 1; i <= n; i++) {
        if(isVis[i]) continue;
        bfs(i); ans++;
    }
    cout << ans;
}