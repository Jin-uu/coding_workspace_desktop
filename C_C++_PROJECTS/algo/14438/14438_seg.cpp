#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>
#define INF INT_MAX
#define MAX 100'000
using namespace std;

constexpr int SZ = 1 << 17;
int n, q, A[SZ], seg_tree[SZ<<1];

void update(int x, int v, int node, int s, int e) {
	if(s == e) {seg_tree[node] = v; return;}
	int m = (s+e)/2;
	if(x <= m) update(x, v, node*2, s, m);
	else update(x, v, node*2+1, m+1, e);
	seg_tree[node] = min(seg_tree[node*2], seg_tree[node*2+1]);
}

int get_min(int l, int r, int node, int s, int e) {
	if(r < s || e < l) return INF;
	if(l <= s && e <= r) return seg_tree[node];
	int m = (s+e)/2;
	return min(get_min(l, r, node*2, s, m), get_min(l, r, node*2+1, m+1, e));
}

void init(int node, int s, int e) {
	if(s==e) { seg_tree[node] = A[s]; return;}
	int m = (s+e) / 2;
	init(node*2, s, m);
	init(node*2+1, m+1, e);
	seg_tree[node] = min(seg_tree[node*2], seg_tree[node*2+1]);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	for(int i=0; i<n; i++) cin >> A[i];
	init(1, 1, n);
	cin >> q;
	int q1, l, r;
	for(int i=0; i<q; i++) {
		cin >> q1 >> l >> r;
		if(q1 == 2) cout << get_min(l-1,r-1, 1, 1, n) << '\n';
		else update(l-1,r, 1, 1, n);
	}
}