#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 1'000'000
using namespace std;

int n, tmp;
int ans[MAX+1];
vector<int> v, st;

int main() {
	ios::sync_with_stdio(false);	cin.tie(NULL);	cout.tie(NULL);
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> tmp; v.push_back(tmp);
	}

	for(int i=v.size()-1; i>=0; i--) {
		while(!st.empty() && (st.back() <= v[i])) st.pop_back();
		if(st.empty()) ans[i] = -1;
		else ans[i] = st.back();
		st.push_back(v[i]);
	}

	for(int i=0; i<n; i++) cout << ans[i] << ' ';
}