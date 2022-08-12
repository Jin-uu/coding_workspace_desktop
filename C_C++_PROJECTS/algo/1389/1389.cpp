#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <cstring>
#define MAX_N 100
#define MAX_M 5000
#define INF INT_MAX
using namespace std;

typedef struct _node {
    int num;
    int depth;
} node;

int n, m;
int dist[MAX_N+1], isChk[MAX_N+1];
vector<int> edge[MAX_N+1];
queue<node> q;

int bfs(int start){
    q = queue<node>(); memset(isChk, false, sizeof(isChk));
    q.push({start,0}); isChk[start] = true;

    int ret=0,from, dep, to;
    while(!q.empty()){
        from = q.front().num; dep = q.front().depth; q.pop();
        ret += dep;
        for (int i = 0; i < edge[from].size(); i++) {
            to = edge[from][i];
            if(isChk[to]) continue;
            isChk[to] = true;
            q.push({to, dep+1});
        }        
    }
    return ret;
}

int main(void){
    cin >> n >> m;
    int from, to;
    for (int i = 0; i < m; i++) {
        cin >> from >> to;
        edge[from].push_back(to);
        edge[to].push_back(from);
    }

    for (int i = 1; i <= n; i++) dist[i] = bfs(i);
    
    int min = INF, ans=-1;
    for (int i = 1; i <= n; i++) {
        if(min > dist[i]) {
            ans = i; min = dist[i];
        }
    }
    cout << ans;
}