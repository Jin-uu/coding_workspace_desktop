#include <iostream>
#include <cstring>
#include <algorithm>
#define MAX_N 100
typedef long long ll;

using namespace std;

int t;
ll dp[MAX_N+10];

ll solve(int n){
    if(n == 0) return 1;
    if(n == 1) return 1;
    if(n == 2) return 1;
    if(n == 3) return 2;
    if(n == 4) return 2;

    ll &ret = dp[n];
    if(ret != -1) return ret;

    return ret = solve(n-1) + solve(n-5);
}

int main(void){
    cin >> t;
    memset(dp, -1, sizeof(dp));
    int n;
    for (int i = 0; i < t; i++) {
        cin >> n;
        cout << solve(n-1) << '\n';
    }   
    
}