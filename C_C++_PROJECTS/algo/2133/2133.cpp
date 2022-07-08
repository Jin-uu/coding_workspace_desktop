#include <iostream>
#include <cstring>

#define MAX_N 30
typedef long long ll;

using namespace std;

int n;
ll dp[MAX_N+1];

ll solve(int n){
    if(n == 0) return 1;
    if(n < 0) return 0;

    ll &ret = dp[n];
    if(ret != -1) return ret;

    ll sum=solve(n-2)*3;
    for (int i = n; i > 2; i-=2) {
        sum += 2*solve(n-i);
    }
    
    return ret = sum;
}

int main(void){
    cin >> n;

    memset(dp, -1, sizeof(dp));
    dp[1] = 0;
    dp[2] = 3;
    dp[3] = 0;
    dp[4] = 11;

    if(n%2) cout << 0;
    else cout << solve(n);
}

