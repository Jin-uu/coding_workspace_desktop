#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX_COST 100'000

// typedef pair<int,int> pii;

using namespace std;

int c, n;
vector<pair<int,int>> input;
int dp_tbl[21][1001];       // dp[i][j] : j번째 까지 사용했을 때 고객을 i명 늘리기 위한 투자금 최소값

int solve(int client, int curr){
    if(curr == 0){
        return dp_tbl[curr][client] = ((client-1)/input[curr].second +1) * input[curr].first;
    }
    if(client == 0) return 0;
    if(client < 0) return 0;
    // cout << client << ", " << curr << endl;
    int &ret = dp_tbl[curr][client];
    if(ret != -1) return ret;

    return ret = min(solve(client - input[curr].second, curr)+input[curr].first, solve(client,curr-1));
}

int main(void){
    cin >> c >> n;
    int temp_c, temp_p;
    for (int i = 0; i < n; i++) {
        cin >> temp_c >> temp_p;
        input.push_back({temp_c, temp_p});
    }
    
    memset(dp_tbl, -1, sizeof(dp_tbl));
    cout << solve(c, n-1) << endl;

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j <= c; j++){
    //         cout << dp_tbl[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    
}



