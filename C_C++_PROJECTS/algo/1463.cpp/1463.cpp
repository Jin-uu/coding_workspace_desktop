#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int N;
int dp[100'0001];

void set_dp(void){
    memset(dp, -1, sizeof dp);
}

int get_dp(int n){
    if(n == 1) return 0;
    if(dp[n] != -1){
        return dp[n];
    }

    int min_dp = 987654321;
    if(n%3 == 0){
        min_dp = min(min_dp, get_dp(n/3)+1);
    }
    if(n%2 == 0){
        min_dp = min(min_dp, get_dp(n/2)+1);
    }    
    min_dp = min(min_dp, get_dp(n-1)+1);
    
    dp[n] = min_dp;
    return dp[n];
}

int main(void){
    cin >> N;
    set_dp();
    cout << get_dp(N);    
}