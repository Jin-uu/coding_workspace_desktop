#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <limits.h>

#define INF INT_MAX
#define MAX_N 1000

using namespace std;

int n, ans=INF;
int MAP[MAX_N+1][3];
int dp_tbl[MAX_N+1][3];
int mem[3];

int solve(int a, int clr){
    if(a<0) return 0;

    int &ret = dp_tbl[a][clr];
    if(ret != -1) return ret;

    int m = INF;
    for (int i = 0; i < 3; i++) {
        if(i != clr) m = min(m, solve(a-1, i));        
    }
    return ret = m + MAP[a][clr];
}

int main(void){
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> MAP[i][0] >> MAP[i][1] >> MAP[i][2];
    }

    for (int i = 0; i < 3; i++) {
        mem[i] = MAP[0][i];
    }
    
    for (int i = 0; i < 3; i++) {
        memset(dp_tbl, -1, sizeof(dp_tbl));
        for (int j = 0; j < 3; j++) {
            MAP[0][j] = mem[j];
        }
        for (int j = 0; j < 3; j++) {
            if(j == i){
                continue;
            }
            MAP[0][j] = 1001;
        }
        for (int j = 0; j < 3; j++) {
            if(j == i) continue;
            ans = min(ans, solve(n-1,j));
        }
    }

    cout << ans;
}