#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <limits.h>

#define INF INT_MAX

using namespace std;

int n;
int MAP[1001][3];
int dp_tbl[1001][3];

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
        for (int j = 0; j < 3; j++) {
            cin >> MAP[i][j];
        }
    }
    
    memset(dp_tbl, -1, sizeof(dp_tbl));

    cout << min({solve(n-1, 0),solve(n-1, 1),solve(n-1, 2)}) << '\n';
}