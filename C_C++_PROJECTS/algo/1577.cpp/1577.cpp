// isBaned에서 한번 꼬임;
#include <iostream>
#include <cstring>

using namespace std;

int N, M, K;
int ban[50][4];
long long dp[101][101];

bool isBaned(int a, int b, int c, int d) {
	for (int i = 0; i < K; i++) {
		if (a != ban[i][0]) continue;
		if (b != ban[i][1]) continue;
		if (c != ban[i][2]) continue;
		if (d != ban[i][3]) continue;
		return true;
	}
	for (int i = 0; i < K; i++) {
		if (a != ban[i][2]) continue;
		if (b != ban[i][3]) continue;
		if (c != ban[i][0]) continue;
		if (d != ban[i][1]) continue;
		return true;
	}
	return false;
}

void set_dp(void) {
	memset(dp, -1, sizeof(dp));
}

long long dfs(int r, int c) {
	if (r > N || c > M) return 0;
	//cout << r << ", " << c << endl;
	if (r == N && c == M) return 1;
	if (dp[r][c] != -1) return dp[r][c];

	long long sum = 0;
	if (!isBaned(r, c, r + 1, c)) {			// 우
		sum += dfs(r + 1, c);
	}
	if (!isBaned(r, c, r, c+1)) {			// 상
		sum += dfs(r, c+1);
	}
	return dp[r][c] = sum;
}

int main(void) {
	cin >> N >> M;
	cin >> K;

	for (int i = 0; i < K; i++) {
		cin >> ban[i][0] >> ban[i][1] >> ban[i][2] >> ban[i][3];
	}

	set_dp();
	
	cout << dfs(0, 0) << endl;
}