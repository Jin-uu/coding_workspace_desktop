#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int N, M, K;
int dp[301][301];
int edge[301][301];

void set_dp(void) {
	memset(dp, -1, sizeof(dp));
}

int get_dp(int start, int cnt) {
	if (cnt == 0  && start != N) return -999999999;
	if (start == N) return 0;

	if (dp[start][cnt] != -1) return dp[start][cnt];

	int max_dp = -999999999;
	for (int target = start + 1; target <= N; target++) {
		if(!edge[start][target]) continue;
		max_dp = max(max_dp, edge[start][target] + get_dp(target, cnt - 1));
	}

	dp[start][cnt] = max_dp;
	return max_dp;
}

int main(void) {
	cin >> N >> M >> K;

	for (int i = 0; i < K; i++) {
		int start, end, score;
		cin >> start >> end >> score;
		edge[start][end] = max(edge[start][end], score);
	}

	set_dp();

	cout << get_dp(1,M-1);
}