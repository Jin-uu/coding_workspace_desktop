#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#define MAX_N 1000
using namespace std;

int n, m, v;
bool isChk[MAX_N+1];
vector<int> edges[MAX_N+1];
queue<int> q;

void dfs(int node){
    cout << node << " "; 
    for (int i = 0; i < edges[node].size(); i++) {
        int next_node = edges[node][i];
        if(isChk[next_node]) continue;
        isChk[next_node] = true;
        dfs(next_node);
    }
}

void bfs(){
    q.push(v);
    isChk[v] = true;
    int curr_node, to;
    while(!q.empty()){
        curr_node = q.front(); q.pop(); cout << curr_node << " ";
        for (int i = 0; i < edges[curr_node].size(); i++) {
            to = edges[curr_node][i];
            if(isChk[to]) continue;
            isChk[to] = true;
            q.push(to);     
        }
    }
}

int main(void){
    cin >> n >> m >> v;
    int temp_x, temp_y;
    for (int i = 0; i < m; i++) {
        cin >> temp_x >> temp_y; edges[temp_x].push_back(temp_y); edges[temp_y].push_back(temp_x);    
    }
    for (int i = 0; i < MAX_N; i++) sort(edges[i].begin(), edges[i].end());        

    isChk[v] = true; dfs(v); cout << endl;
    memset(isChk, false, sizeof(isChk)); bfs();
}
