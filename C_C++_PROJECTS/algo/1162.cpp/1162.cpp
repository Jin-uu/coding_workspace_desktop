#include <bits/stdc++.h>
#define MAX_N 10000
#define MAX_M 50000
#define MAX_K 20
#define INF LLONG_MAX
typedef long long ll;
using namespace std;

int N, M, K;
vector<pair<int,ll>> edges[MAX_N+1];
ll dist[MAX_N+1][MAX_K+1];

void dijkstra(int start){    
    dist[start][0] = 0;
    priority_queue<pair<ll, pair<int,int>>> pq;
    pq.push({0,{start, 0}});

    while(!pq.empty()){
        int curr = pq.top().second.first;
        int cnt = pq.top().second.second;
        ll cost = -pq.top().first;
        pq.pop();
        if(dist[curr][cnt] < cost) continue;
        
        for (int i = 0; i < edges[curr].size(); i++) {
            int next_node = edges[curr][i].first;
            ll next_cost = cost + edges[curr][i].second;

            if(dist[next_node][cnt] > next_cost){
                dist[next_node][cnt] = next_cost;
                pq.push({-next_cost,{next_node,cnt}});
            }

            if(dist[next_node][cnt+1] > cost && cnt+1 <= K){
                dist[next_node][cnt+1] = cost;
                pq.push({-cost,{next_node,cnt+1}});
            }
        }        
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cin.tie(NULL);

    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int a, b, dist;
        cin >> a >> b >> dist;
        edges[a].push_back({b,dist});
        edges[b].push_back({a,dist});
    }
    
    for (int i = 0; i < MAX_N+1; i++) {
        for (int j = 0; j < MAX_K+1; j++){
            dist[i][j] = INF;
        }
    }
    dijkstra(1);

    ll ans = INF;
    for (size_t i = 0; i <= K; i++) {
        ans = min(ans, dist[N][i]);
    }

    cout << ans;    

    return 0;
}
