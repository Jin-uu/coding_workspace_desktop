#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>

#define MAX_S 300

using namespace std;

int n;
int S[MAX_S+1];
int dp[MAX_S+1];

int DP(int n){
    if(n == 0) return S[0];
    if(n == 1) return S[0] + S[1];
    if(n == 2) return max(S[0]+S[2], S[1]+S[2]);

    int &ret = dp[n];
    if(ret != -1) return ret;

    return ret = max(DP(n-3) + S[n-1], DP(n-2)) + S[n];
}

int main(void){
    cin >> n;
    for (int i = 0; i < n; i++) cin >> S[i];

    memset(dp, -1, sizeof(dp));
    cout << DP(n-1);
}