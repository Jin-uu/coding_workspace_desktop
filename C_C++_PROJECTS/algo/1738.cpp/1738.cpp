#include <bits/stdc++.h>
#define MAX_N 100
#define MAX_M 20000
#define INF LLONG_MAX

using namespace std;

int N,M;
vector<pair<int,int>> edges[MAX_N+1];
vector<pair<int,int>> rev_edges[MAX_N+1];
bool canReach[MAX_N+1];
long long dist[MAX_N+1];
int route[MAX_N+1];
bool pos=true;

void check() {
    queue<int> q;
    q.push(N);
    canReach[N] = true;

    while(!q.empty()){
        int curr = q.front(); q.pop();
        for(int i=0; i<rev_edges[curr].size(); i++){
            int curr_target = rev_edges[curr][i].first;
            if(canReach[curr_target] == false){
                q.push(curr_target);
                canReach[curr_target] = true;
            }
        }
    }

}

void bellman(){
    dist[1] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 0; k < edges[j].size(); k++) {
                // printf("%d %d %d \n",i,j,k);
                int curr_target = edges[j][k].first;
                int curr_weight = edges[j][k].second;
                if(dist[j] == INF) continue;
                if(dist[curr_target] > dist[j] + curr_weight){
                    route[curr_target] = j;
                    dist[curr_target] = dist[j] + curr_weight;
                    if((i == N-1) && (canReach[j])){
                        cout << -1 <<'\n';
                        pos=false;
                        return;
                    }
                }
            }            
        }        
    }    
}

void print_ans(int curr){
    if(curr==0) return;
    print_ans(route[curr]);
    cout << curr << " ";
}

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        edges[u].push_back({v,-w});
        rev_edges[v].push_back({u,-w});        
    }

    check();

    if(canReach[1] == false){
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i <= MAX_N; i++) {
        dist[i] = INF;
    }

    bellman();
    
    if(pos) print_ans(N);
}