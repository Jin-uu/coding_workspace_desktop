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
	if (left == right) return 0;
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

bool isPossible(int score) {
	bool check = true;
	int left = 1;
	int cnt=0;
	for (int i = 1; i <= N; i++) {
		int curr_score = get_scores(left, i);
		if (score < get_scores(left, i)) {
			cnt++;
			if (cnt >= M) return false;
			left = i;
		}
	}
	return true;
}

int get_ans(void) {
	int mid;
	int left = 0;
	int right = 10000;
	int ans = 987654321;

	while (left <= right ) {
		mid = (left + right) / 2;
		//cout <<left << ", " << mid << ", " << right << ": " << isPossible(mid) << "/" ;
		if (isPossible(mid)) {
			right = mid - 1;
			ans = mid;
		}
		else {
			left = mid + 1;
		}
		//cout << ans << endl;
	}
	return ans;
}


int main(void) {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		cin >> nums[i];
	}
	set_scores();

	cout << get_ans() <<endl;
}