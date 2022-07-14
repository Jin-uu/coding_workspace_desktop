#include <iostream>
#define MAX_N 1000

using namespace std;

int t;
int dp[MAX_N+1][10];

void init(void){
    for (int i = 0; i < 10; i++) {
        dp[1][i] = 1;
    }
}

void solve(void){
    for (int i = 2; i <= MAX_N; i++) {
        dp[i][0] = (dp[i-1][7]) % 1234567;
        dp[i][1] = (dp[i-1][2] + dp[i-1][4]) % 1234567;
        dp[i][2] = (dp[i-1][1] + dp[i-1][3] + dp[i-1][5]) % 1234567;
        dp[i][3] = (dp[i-1][2] + dp[i-1][6]) % 1234567;
        dp[i][4] = (dp[i-1][1] + dp[i-1][5] + dp[i-1][7]) % 1234567;
        dp[i][5] = (dp[i-1][2] + dp[i-1][4] + dp[i-1][6] + dp[i-1][8]) % 1234567;
        dp[i][6] = (dp[i-1][3] + dp[i-1][5] + dp[i-1][9]) % 1234567;
        dp[i][7] = (dp[i-1][0] + dp[i-1][4] + dp[i-1][8]) % 1234567;
        dp[i][8] = (dp[i-1][5] + dp[i-1][7] + dp[i-1][9]) % 1234567;
        dp[i][9] = (dp[i-1][6] + dp[i-1][8]) % 1234567;
    }
}

int sum(int n){
    int s=0;
    for (int i = 0; i < 10; i++){
        s = (s + dp[n][i]) % 1234567;
    }
    return s;
}

int main(void){
    cin >> t;
    int n;
    init(); solve();
    for (int i = 0; i < t; i++) {
        cin >> n;
        cout << sum(n) << endl;
    }
}