#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int N, S;
vector<pair<int,int>> paints;
int dp[300001];		// dp[i] : 0번째~i번째 사용 했을 때의 최대합

void set_dp(void) {
	memset(dp, -1, sizeof(dp));
}

bool bound_compare(pair<int, int> a, pair<int, int> b) {
	return a.first < b.first;
}

int get_dp(int n) {
	if (n >= N) return 0;

	if (dp[n] != -1) return dp[n];

	int max_dp = 0;
	int first_case = get_dp(n + 1);
	pair<int, int> target_pair;
	target_pair.first = paints[n].first + S;
	int second_case = paints[n].second + get_dp(lower_bound(paints.begin(), paints.end(), target_pair, bound_compare) - paints.begin());
	max_dp = max(first_case, second_case);
	dp[n] = max_dp;
	return dp[n];
}

bool compare(pair<int, int> a, pair<int, int> b) {
	if (a.first == b.first) {
		return a.second < b.second;
	}
	else
		return a.first < b.first;
}

int main(void) {
	cin >> N >> S;

	for (int i = 0; i < N; i++) {
		pair<int,int> temp;
		cin >> temp.first >> temp.second;
		paints.push_back(temp);
	}

	sort(paints.begin(), paints.end(), compare);

	set_dp();
	cout << get_dp(0);
}