#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 200000

typedef long long ll;

using namespace std;

ll m, n, total;
int parent[MAX + 10];
vector<pair<int, pair<int, int>>> edge;


void init(void) {
	for (int i = 0; i <= m; i++) {
		parent[i] = i;
	}
}

int find_parent(int a) {
	if (a == parent[a]) return a;
	else return parent[a] = find_parent(parent[a]);
}

void union_parent(int a, int b) {
	a = find_parent(a);
	b = find_parent(b);

	if (a < b) parent[b] = a;
	else parent[a] = b;
}

bool is_same_p(int a, int b) {
	if (find_parent(a) == find_parent(b)) return  true;
	return false;
}

int main(void) {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	while(1) {
		cin >> m >> n;
		if (m == 0 && n == 0) break;
		total = 0;
		edge.clear();
		int temp_x, temp_y, temp_z;
		for (int i = 0; i < n; i++) {
			cin >> temp_x >> temp_y >> temp_z;
			edge.push_back({ temp_z,{ temp_x,temp_y } });
			total += temp_z;
		}
		init();
		sort(edge.begin(), edge.end());
		ll sum = 0;
		for (int i = 0; i < edge.size(); i++) {
			if (!is_same_p(edge[i].second.first, edge[i].second.second)) {
				sum += edge[i].first;
				union_parent(edge[i].second.first, edge[i].second.second);
			}
		}

		cout << total - sum << endl;
	}
}




