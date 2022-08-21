#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX_N 100'000
using namespace std;

int t, n;
int MAP[2][MAX_N+1];
int dp_tbl[2][MAX_N+1];

int solve(int h, int curr){
    if(curr == 0) return MAP[h][curr];
    if(curr < 0) return 0;

    int &ret = dp_tbl[h][curr];
    if(ret != -1) return ret;

    return ret = max(solve(!h,curr-1) , solve(!h, curr-2)) + MAP[h][curr]    ;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> t;
    for (int i = 0; i < t; i++) {
        memset(MAP, -1, sizeof(MAP));
        memset(dp_tbl, -1, sizeof(dp_tbl));
        cin >> n;
        for (int i = 0; i < 2; i++) for (int j = 0; j < n; j++) cin >> MAP[i][j];
        cout << max(solve(0, n-1), solve(1, n-1)) << '\n';
    }
}