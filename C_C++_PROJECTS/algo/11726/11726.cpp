#include <iostream>
#include <cstring>

using namespace std;

int n;
int dp[1010];

int solve(int n){
    if(n == 1) return 1;
    if(n == 2) return 2;

    int &ret = dp[n];
    if(ret != -1) return ret;

    return ret = (solve(n-1) + solve(n-2)) % 10007;
}

int main(void){
    cin >> n;
    memset(dp, -1, sizeof(dp));

    cout << solve(n);
}