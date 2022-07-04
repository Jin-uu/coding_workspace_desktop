#include <iostream>
#include <cstring>
#include <algorithm>
typedef long long ll;

using namespace std;

int N;
ll dp[91];

ll solve(int n){
    if(n == 1 || n == 2) return 1;
    if(dp[n] != -1) return dp[n];
    return dp[n] = solve(n-1) + solve(n-2);
}

int main(void){
    cin >> N;
    memset(dp, -1, sizeof(dp));
    cout << solve(N);
}