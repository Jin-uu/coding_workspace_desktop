#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstring>


using namespace std;

string str;
int dp[2501];
int isPalin_arr[2501][2501];

void set_isPalin_arr(void) {
	memset(isPalin_arr, -1, sizeof(isPalin_arr));
}

bool isPalin(int r, int c) {
	if (isPalin_arr[r][c] != -1) return isPalin_arr[r][c];
	for (int i = 0; i <= (c - r + 1)/2; i++) {
		if (str[r + i] != str[c - i]) return isPalin_arr[r][c] = false;
	}
	return isPalin_arr[r][c] = true;
}

void set_dp() {
	memset(dp, -1, sizeof(dp));
	dp[0] = 1;
}

int get_dp(int c) {
	//cout << "(" << 0 << ", " << c << ")" << endl;
	if (0 > c) return 0;
	if (0 == c) return 1;
	if (dp[c] != -1) return dp[c];

	int min_dp = 2500;
	for (int i = 0; i <= c; i++) {
		if (isPalin(i, c)) min_dp = min(min_dp, get_dp(i - 1) + 1);
	}
	dp[c] = min_dp;
	return dp[c];
	//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
}

int main(void) {
	cin >> str;
	set_dp();
	set_isPalin_arr();
	cout << get_dp(str.length()-1);
}