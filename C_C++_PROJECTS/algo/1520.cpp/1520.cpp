// dp 없이 풀었다가 시간초과나서 dp 적용

#include <iostream>
#include <cstring>

using namespace std;

int N, M;
int map[502][502];
int dp[502][502];
int ans = 0;

void set_dp(void) {
	memset(dp, -1, sizeof(dp));
	dp[N][M] = 1;
}
void set_map(void) {
	for (int i = 0; i <= N+1; i++) {
		map[i][0] = 10001;
		map[i][M + 1] = 10001;
	}
	for (int j = 0; j <= M+1; j++) {
		map[0][j] = 10001;
		map[N + 1][j] = 10001;
	}
}

int dfs(int r, int c) {
	if (dp[r][c] != -1) return dp[r][c];
	if (r == N && c == M) {
		return 1;
	}
	int sum = 0;

	if (map[r][c] > map[r - 1][c]) {
		sum += dfs(r - 1, c);
	}
	if (map[r][c] > map[r + 1][c]) {
		sum += dfs(r + 1, c);
	}
	if (map[r][c] > map[r][c - 1]) {

		sum += dfs(r, c - 1);
	}
	if (map[r][c] > map[r][c + 1]) {
		sum += dfs(r, c + 1);
	}
	dp[r][c] = sum;
	return sum;
}

int main(void) {
	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}

	set_map();
	set_dp();
	cout << dfs(1,1);
}