#include <iostream>
#include <cstring>
#define MAX_N 1000
#define DIV 10007
using namespace std;

int n;
int dp_tbl[MAX_N+1];

int solve(int n){
    if(n < 0) return 0; if(n <= 1) return 1;

    int &ret = dp_tbl[n];
    if(ret != -1) return ret;
    return ret = (solve(n-1) + solve(n-2)*2) % DIV;
}

int main(void){
    cin >> n;
    memset(dp_tbl, -1, sizeof(dp_tbl));
    cout << solve(n);
}