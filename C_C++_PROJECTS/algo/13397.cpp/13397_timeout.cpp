// dp인줄 알고 열심히 짰으나 이분탐색이었다.

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M;
int nums[5005];
int scores[5005][5005];
int dp[5005][5005];

void set_scores(void) {
	memset(scores, -1, sizeof(scores));
}


int get_scores(int left, int right) {
	if (scores[left][right] != -1) return scores[left][right];
	int min_score = 987654321;
	int max_score = 0;

	for (int i = left; i <= right; i++) {
		min_score = min(min_score, nums[i]);
		max_score = max(max_score, nums[i]);
	}

	return max_score - min_score;
}

void set_dp(void) {
	memset(dp, -1, sizeof(dp));
}

int get_dp(int n, int c) {
	if (n < c) return 0;
	if (c == 1) return get_scores(1,n);

	if (dp[n][c] != -1) return dp[n][c];

	int min_dp = 987654321;
	for (int i = c; i <= n; i++) {
		int left = get_dp(i - 1, c - 1);
		int right = get_scores(i, n);
		min_dp = min(min_dp,max(left, right));
	}
	dp[n][c] = min_dp;
	return min_dp;
}

int main(void) {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		cin >> nums[i];
	}
	set_dp();
	set_scores();
	cout << get_dp(N,M) << endl;
}