#include <iostream>
#include <cstring>
#include <vector>

#define MAX_T 10000
#define MAX_K 100

using namespace std;

int t, k;
vector<pair<int,int>> coins;
int dp[MAX_T+1][MAX_K+1];

int solve(int cash, int cnt){
    if(cash == 0) return 1;
    if(cnt >= k || cash < 0) return 0;

    int &ret = dp[cash][cnt];
    if(ret != -1) return ret;

    int sum=0;
    for (int i = 0; i <= coins[cnt].second; i++){
        sum += solve(cash - coins[cnt].first*i, cnt+1);
    }
    return ret = sum;
}

int main(void){
    cin >> t >> k;
    int temp_coin, temp_cnt;
    for (int i = 0; i < k; i++) {
        cin >> temp_coin >> temp_cnt;
        coins.push_back({temp_coin, temp_cnt});
    }
    memset(dp, -1, sizeof(dp));
    cout << solve(t,0);
}

