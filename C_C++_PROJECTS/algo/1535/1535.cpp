#include <iostream>
#include <cstring>
#include <algorithm>
#define MAX_N 20

using namespace std;

int n;
int dp_tbl[MAX_N+1][101];
int L[MAX_N+1], J[MAX_N+1];

int solve(int curr, int hp){
    if(hp <= 0 || curr < 0) return 0;

    int &ret = dp_tbl[curr][hp];
    if(ret != -1) return ret;

    if(L[curr] >= hp) return ret = solve(curr-1,hp);
    return ret = max(solve(curr-1, hp), solve(curr-1,hp-L[curr]) + J[curr]);
}

int main(void){
    cin >> n;
    for (int i = 0; i < n; i++) cin >> L[i];
    for (int i = 0; i < n; i++) cin >> J[i];
    
    memset(dp_tbl, -1, sizeof(dp_tbl));
    
    cout << solve(n,100) << endl;
}