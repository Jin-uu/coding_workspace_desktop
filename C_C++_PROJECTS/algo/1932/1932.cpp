#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX_N 500

using namespace std;

int n;
int tri[MAX_N+1][MAX_N+1];
int dp_tbl[MAX_N+1][MAX_N+1];


int solve(int r, int c){
    if(r >= n) return 0;

    int &ret = dp_tbl[r][c];
    if(ret != -1) return ret;

    return ret = max(solve(r+1,c),solve(r+1,c+1))+tri[r][c];
}

int main(void){
    cin >> n;
    int cnt=1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < cnt; j++) {
            cin >> tri[i][j];
        }
        cnt++;
    }
    memset(dp_tbl, -1, sizeof(dp_tbl));
    cout << solve(0,0) << endl;    

}