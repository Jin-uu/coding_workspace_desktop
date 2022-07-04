#include <iostream>
#include <cstring>
#include <algorithm>
typedef long long ll;

using namespace std;

int N;
ll dp[91];

void solve(void){
    for (int i = 3; i <= 90; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }    
}

int main(void){
    cin >> N;
    dp[1] = 1;
    dp[2] = 1;

    solve();
    cout << dp[N];

}