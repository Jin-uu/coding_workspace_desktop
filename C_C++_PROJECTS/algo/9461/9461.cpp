#include <iostream>
#include <cstring>
#include <algorithm>
#define MAX_N 100
typedef long long ll;

using namespace std;

int t, n;
ll dp[MAX_N+10];

void init(void){
    memset(dp, -1, sizeof(dp));
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 2;
    dp[4] = 2;
}

void solve(void){
    for (int i = 5; i < MAX_N+1; i++){
        dp[i] = dp[i-1] + dp[i-5];
    }    
}

int main(void){
    cin >> t;
    init();
    solve();    
    for (int i = 0; i < t; i++) {
        cin >> n;
        cout << dp[n-1] << '\n';
    }   
    
}