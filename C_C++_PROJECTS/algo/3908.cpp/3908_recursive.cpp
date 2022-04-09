// 3908
// 재귀로 풀었는데 망함...
#define DEBUG
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>



using namespace std;

int T;
vector<vector<int>> test_case;
bool isPrime[1121];
int dp[1201][15];

void set_isPrime(void) {
	memset(isPrime, true, 1121);
	isPrime[1] = false;
	for (int i = 2; i <= 1120; i++) {
		if (!isPrime[i]) continue;
		for (int j = i * 2; j <= 1120; j += i) {
			isPrime[j] = false;
		}
	}
}

int rec_dp(int n, int div, int last) {
	if (dp[n][div] != -1) return dp[n][div];
	if (div == 1) {
		if (isPrime[n]) return 1;
		return 0;
	}
	dp[n][div] = 0;
	for (int i = last+1; i < n/2; i++) {
		if (!isPrime[i]) continue;
#ifdef DEBUG
		cout << "rec_dp(" << n << ", " << div << ", " << last << ") :" << i << endl;
#endif
		dp[n][div] += rec_dp(n - i, div - 1, i);
	}

	return dp[n][div];
}

int main(void) {
	cin >> T;

	for (int i = 0; i < T; i++) {
		int n, k;
		cin >> n >> k;
		vector<int> temp_input;
		temp_input.push_back(n);

		temp_input.push_back(k);
		test_case.push_back(temp_input);
	}

	#ifdef DEBUG
		cout << "//>> input :" << endl;
		for (int i = 0; i < T; i++) {
			cout << test_case[i][0] << ", " << test_case[i][1] << endl;
		}
		cout << "--------------------" << endl;
	#endif

		set_isPrime();

	#ifdef DEBUG
		int prime_cnt = 0;
		cout << "//>> isPrime[] :" << endl;
		for (int i = 2; i <= 1120; i++) {
			if (isPrime[i]) { cout << i << "   "; prime_cnt++; }
		}
		cout << endl << "//>> prime_cnt : " << prime_cnt;
		cout << endl << "--------------------" << endl;
	#endif

		memset(dp, -1, sizeof(dp));

		for (int i = 0; i < T; i++){
#ifdef DEBUG
			cout << test_case[i][0] << ", " << test_case[i][1] << ": ";
#endif
			cout << rec_dp(test_case[i][0], test_case[i][1], 1) << endl;
		}

		for (int i = 0; i < T; i++) {
#ifdef DEBUG
			cout << test_case[i][0] << ", " << test_case[i][1] << ": ";
#endif
			cout << rec_dp(test_case[i][0], test_case[i][1], 1) << endl;
		}

	return 0;
}
