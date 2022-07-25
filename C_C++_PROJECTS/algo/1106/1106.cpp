#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX_COST 100'000

using namespace std;

int c, n;
vector<pair<int,int>> input;
int dp_tbl[21][1001];

int solve(int client, int curr){
    if(client <= 0) return 0;
    if(curr == 0) return dp_tbl[curr][client] = ((client-1)/input[curr].second +1) * input[curr].first;
    

    int &ret = dp_tbl[curr][client];
    if(ret != -1) return ret;

    int curr_cost = input[curr].first, curr_client = input[curr].second;
    return ret = min(solve(client - curr_client, curr)+curr_cost, solve(client,curr-1));
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
}