#include <iostream>
#define MAX 1515
#define DIV 1'000'000'007
using namespace std;

int n;
int dp_tbl[3][MAX+1];

int main() {
   ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    dp_tbl[0][0] = 1; dp_tbl[1][0] = 1; dp_tbl[2][0] = 0;
    dp_tbl[0][1] = 1; dp_tbl[1][1] = 1; dp_tbl[2][1] = 2;

    for (int i = 2; i < n; i++) {
        dp_tbl[0][i] = (dp_tbl[1][i-1] + dp_tbl[2][i-1]) % DIV;
        dp_tbl[1][i] = (dp_tbl[0][i-1] + dp_tbl[2][i-1]) % DIV;
        dp_tbl[2][i] = (dp_tbl[0][i-1] + dp_tbl[1][i-1]) % DIV;
    }
    cout << dp_tbl[0][n-2];
}