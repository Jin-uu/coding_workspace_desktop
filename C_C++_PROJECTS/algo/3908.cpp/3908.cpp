// 3908
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>



using namespace std;

int T;
vector<vector<int>> test_case;
bool isPrime[1121];
int dp[1121][15];

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

void set_dp() {
	dp[0][0] = 1;
	for (int p = 1; p <= 1120; p++) {
		if (!isPrime[p]) continue;
		for (int i = 1120; i >= p; i--) {
			for (int j = 1; j <= 14; j++) {
				dp[i][j] += dp[i - p][j - 1];
			}
		}
	}
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

	set_isPrime();
	set_dp();

	for (int testCaseNum = 0; testCaseNum < T; testCaseNum++){
		//cout << testCaseNum << ": " << test_case[testCaseNum][0] << ", " << test_case[testCaseNum][1] << ": ";
		cout << dp[test_case[testCaseNum][0]][test_case[testCaseNum][1]] << endl;
	}


	return 0;
}
