#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAX_T 10000
#define MAX_K 100

using namespace std;

int t, k;
vector<pair<int,int>> coins;
int dp[MAX_T+1];

void __debug_print_dp(void){
    for (int i = 0; i <= t; i++)
    {
        cout << dp[i] << " ";
    }
    cout << endl;
}

int main(void){
    cin >> t >> k;
    
    int temp_coin, temp_num;
    for (int i = 0; i < k; i++) {
        cin >> temp_coin >> temp_num;
        coins.push_back({temp_coin, temp_num});
    }
    
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int coin_idx = 0; coin_idx <= k; coin_idx++) {
        for (int val = t; val >= 1; val--) {
            for (int coin_cnt = 1; coin_cnt <= coins[coin_idx].second; coin_cnt++) {
                if(val - coins[coin_idx].first*coin_cnt < 0) continue;
                dp[val] += dp[val - coins[coin_idx].first*coin_cnt];
            }
        }
        // __debug_print_dp();
    }
    
    cout << dp[t];
}







