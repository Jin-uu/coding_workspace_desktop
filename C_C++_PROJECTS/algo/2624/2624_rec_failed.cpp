#include <iostream>
#include <cstring>
#include <vector>

#define MAX_T 10000
#define MAX_K 100

using namespace std;

int t, k;
vector<pair<int,int>> coins;
int dp[MAX_T+1];

void solve(int cash, int cnt){
    if(cash > t) return;
    if(cnt == k) { dp[cash]++; return; }

    for (int i = 0; i <= coins[cnt].second; i++){
        solve(cash+coins[cnt].first*i,cnt+1);
    }
}

int main(void){
    cin >> t >> k;
    int temp_coin, temp_cnt;
    for (int i = 0; i < k; i++) {
        cin >> temp_coin >> temp_cnt;
        coins.push_back({temp_coin, temp_cnt});
    }
    dp[0] = 1;
    solve(0,0);
    cout << dp[t];
}

