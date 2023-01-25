#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define MAX_N 1000
using namespace std;

int t, n, m;
int D[MAX_N+2], COPY[MAX_N+2], into[MAX_N+2];

int solve() {
  vector<int> grph[MAX_N+2];
  cin >> n >> m;
  for(int i=1; i<=n; i++) cin >> D[i];
  int temp_from, temp_to;
  for(int i=1; i<=m; i++) {
    cin >> temp_from >> temp_to;
    grph[temp_from].push_back(temp_to);
    into[temp_to]++;
  }

  queue<int> q;
  for(int i=1; i<=n; i++) COPY[i] = D[i];
  for(int i=1; i<=n; i++) if(into[i] == 0) q.push(i);
  while(!q.empty()) {
    int v = q.front(); q.pop();
    for(auto i : grph[v]) {
      COPY[i] = max(COPY[i], COPY[v] + D[i]);
      if(!--into[i]) q.push(i);
    }
  }
  int temp_w; cin >> temp_w;
  return COPY[temp_w];
}

int main() {
  ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  cin >> t;
  for(int i=0; i<t; i++) cout << solve() << '\n';
}