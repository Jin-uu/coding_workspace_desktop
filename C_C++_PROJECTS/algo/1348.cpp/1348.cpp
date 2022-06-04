#include <bits/stdc++.h>
#define MAX_RC 50
#define MAX_N 100
#define INF 

using namespace std;

typedef long long ll;

int R, C, M=-1;
int b[MAX_N];
vector<pair<int, int>> g[MAX_N];
vector<int> car;
bool is_visited[MAX_N];
char pk[MAX_N][MAX_N];
map<int, int> parking;

bool dfs(int curr, int m) {
    if (is_visited[curr]) return false;
    is_visited[curr] = true;
    for (auto e : g[curr]) {
        if (e.second<=m&&(b[e.first]==-1||dfs(b[e.first], m))) {
            b[e.first] = curr;
            return true;
        }
    }
    return false;
}

void bfs(int i){
    queue<int> q;
    int dy[4] = {0,0,1,-1}, dx[4] = {1,-1,0,0};
    vector<int> dist = vector<int>(R*C, -1);
    dist[car[i]] = 0;
    q.push(car[i]);
    while (!q.empty()) {
        int y = q.front()/C, x = q.front()%C;
        int here = q.front();
        q.pop();
        for (int k=0; k<4; ++k) {
            int ny = y+dy[k], nx = x+dx[k];
            int there = ny*C+nx;
            if (ny<0||nx<0||ny>=R||nx>=C||pk[ny][nx]=='X') continue;
            if (dist[there]==-1) {
                if (parking.count(there)==1) {
                    M = max(M, dist[here]+1);
                    g[i].push_back(make_pair(parking[there], dist[here]+1)); 
                }
                dist[there] = dist[here]+1;
                q.push(there);
            }
        }
    }
}

int match(int m) {
    memset(b, -1, sizeof b);
    int size = 0;
    for (int i=0; i<car.size(); ++i) {
        memset(is_visited, 0, sizeof(is_visited));
        if (dfs(i, m)) ++size;    
    }
    return size;
}

int main(){
    cin >> R >> C;
    int cnt=0;
    for (int i = 0; i < R; i++) {
        scanf("%s", pk[i]);
    }
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(pk[i][j]=='P'){
                parking[i*C+j] = cnt++;                
            }
            else if(pk[i][j] == 'C') {
                car.push_back(i*C+j);
            }
        }
    }
    for(int i=0; i<car.size(); i++){
        bfs(i);
    }
    int left=-1, right=M+1;
    while (left+1<right) {
        int mid = (left+right)/2;
        if (match(mid)<car.size()) left = mid;
        else right = mid;
    }
    if (match(right)==car.size()) cout << right;
    else cout << -1;   

}

