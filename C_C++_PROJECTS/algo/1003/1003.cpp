#include <iostream>
#include <cstring>
#define MAX_N 40
using namespace std;

int t,n;
int dp_tbl[2][MAX_N+1];

void solve(int n){
    if(n <= 1) return;

    int &ret = dp_tbl[0][n];
    if(ret != -1) return;

    solve(n-1); solve(n-2);
    dp_tbl[0][n] = dp_tbl[0][n-1] + dp_tbl[0][n-2];
    dp_tbl[1][n] = dp_tbl[1][n-1] + dp_tbl[1][n-2];
}


int main(void){
    cin >> t;
    memset(dp_tbl, -1, sizeof(dp_tbl));
    dp_tbl[0][0] = 1; dp_tbl[1][0] = 0; dp_tbl[0][1] = 0; dp_tbl[1][1] = 1;
    
    for (int i = 0; i < t; i++){
        cin >> n; solve(n);
        cout << dp_tbl[0][n] << " " << dp_tbl[1][n] << '\n';
    }
}