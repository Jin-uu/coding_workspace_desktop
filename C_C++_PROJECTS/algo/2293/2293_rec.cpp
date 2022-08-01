#include <iostream>
#include <vector>
#include <cstring>
#define MAX_N 100
#define MAX_K 10000

using namespace std;

int n,k, curr;
int dp_tbl[MAX_N+1][MAX_K+1];
vector<int> coin;

int solve(int idx, int val){
    if(idx < 0 || val < 0) return 0;
    if(val == 0) return 1;

    int &ret = dp_tbl[idx][val];
    if(ret != -1) return ret;

    return ret = solve(idx-1, val) + solve(idx, val-coin[idx]);
}

int main(void){
    cin >> n >> k;
    coin.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> coin[i];
    }
    memset(dp_tbl, -1, sizeof(dp_tbl));    

    cout << solve(n-1, k);
}