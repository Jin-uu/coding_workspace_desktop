#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int N;
int nums[5005];
int dp[5005][5005];

void set_dp(void) {
	memset(dp, -1, sizeof(dp));
	dp[1][1] = 0;
}
// 1 2 3 4 5 6 7 8 9 1 1 2 3 4 5 6 7 8 9 1 1 2 3 4 5 6 7 8 9 1 1 2 3 4 5 6 7 8 9 1 1 2 3 4 5 6 7 8 9 1 1 2 3 4 5 6 7 8 9 1 1 2 3 4 5 6 7 8 9 1 1 2 3 4 5 6 7 8 9 1 1 2 3 4 5 6 7 8 9 1 1 2 3 4 5 6 7 8 9 1 

int get_dp(int left, int right) {
	//cout << left << ", " << right << endl;
	if (left >= right) return 0;
	if (left == right - 1) {
		if (nums[left] == nums[right]) return dp[left][right] = 0;
		else return dp[left][right] = 1;
	}


	if (dp[left][right] != -1) return dp[left][right];

	int min_dp = 5001;
	if (nums[left] == nums[right]) {
		min_dp = min(min_dp, get_dp(left + 1, right - 1));
	}
	else {
		min_dp = min(min_dp, min( get_dp(left, right - 1) + 1, get_dp(left+1,right)+1));
	}
	return dp[left][right] = min_dp;
}

int main(void) {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> nums[i];
	}
	nums[0] = -1;

	set_dp();
	cout << get_dp(1, N);

}