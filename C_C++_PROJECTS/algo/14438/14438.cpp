#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>
#define INF INT_MAX
#define MAX 100'000
using namespace std;

int n, q, B = 400;
vector<int> v, div_min;

void calc_min(int div_idx) {
	int left = div_idx*B; int right = min(n-1, (div_idx+1)*B-1);
	div_min[div_idx] = INF;
	for(int i=left; i<=right; i++) {
		div_min[div_idx] = min(div_min[div_idx], v[i]);
	}
}

void update(int idx, int new_val) {
  v[idx] = new_val;
	calc_min(idx/B);
}

int get_min(int left, int right) {
	int ret = INF;
	while(left <= right && left % B != 0) {
		ret = min(ret, v[left]); left++;
	}
	while(left <= right && right % B != B-1) {
		ret = min(ret, v[right]); right--;
	}
	if(left <= right) for(int i=left/B; i<=right/B; i++) ret = min(ret, div_min[i]);
	return ret;
}

void init() {
	for(int i=0; i*B<n; i++) calc_min(i);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n; v.resize(n);
	div_min.resize(n/B+1);
	for(int i=0; i<n; i++) {
		cin >> v[i];
	}
	init();
	
	cin >> q;
	int q1, l, r;
	for(int i=0; i<q; i++) {
		cin >> q1 >> l >> r;
		if(q1 == 2) cout << get_min(l-1,r-1) << endl;
		else update(l-1,r);
	}
}