#include <bits/stdc++.h>

#define MAX_NODE 52
#define INF 1e9

using namespace std;

int N;
int capacity[MAX_NODE][MAX_NODE];
int flow[MAX_NODE][MAX_NODE];
int visited[MAX_NODE];
vector<int> path[MAX_NODE];
int ans=0;

int ctoi(char c){    
    if (c <= 'Z') return c - 'A';		// 대문자
    return c - 'a' + 26; 				// 소문자
}

int solve(){
	int src = ctoi('A');
	int sink = ctoi('Z');

	while (1) {
		memset(visited, -1, sizeof(visited));
		queue<int> q;
		q.push(src);
		//while (!q.empty() && visited[sink] == -1)
		  while (!q.empty()){
			int curr = q.front(); q.pop();
			if(curr == sink) break;
			for (int i = 0; i < path[curr].size(); i++) {
				int next = path[curr][i];
				if(visited[next] == -1 && (flow[curr][next] < capacity[curr][next])){
					visited[next] = curr;
					q.push(next);
					// if(next == sink) break;
				}
			}
			// if(visited[sink] != -1) break;
		}
		if (visited[sink] == -1) break;
		int m = INF;
		for (int i = sink; i != src; i = visited[i]) {
			m = min(capacity[visited[i]][i] - flow[visited[i]][i], m);
		}
		for (int i = sink; i != src; i = visited[i]) {
			flow[visited[i]][i] += m;
			flow[i][visited[i]] -= m;
		}
		ans += m;
	}	
}

int main(void){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	// memset(capacity, 0, sizeof(capacity));
	// memset(flow, 0, sizeof(flow));
	cin >> N;
	for(int i=0;  i<N; i++){
		char  from_c, to_c; int cap;
		cin >> from_c >> to_c >> cap;
		int from = ctoi(from_c);
		int to = ctoi(to_c);

		capacity[from][to] += cap;
		capacity[to][from] += cap;
		
		path[from].push_back(to);
		path[to].push_back(from);
	}
	solve();
	cout << ans << '\n';
	return 0;
}