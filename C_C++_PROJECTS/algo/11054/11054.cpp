#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define MAX_N 1'000
using namespace std;

int n, m;
int dp_L[MAX_N+1];
int dp_R[MAX_N+1];
vector<int> v;

int solve_L(int curr) {
    if(curr < 0) return 0;
    if(curr == 0) return 1;

    int& ret = dp_L[curr];
    if(ret != -1) return ret;

    m = 0;
    for (int i = curr-1; i >= 0; i--) if(v[i] < v[curr]) m = max(m, solve_L(i));    
    // for (int i = 0; i < curr; i++) if(v[i] < v[curr]) m = max(m, solve_L(i));
    return ret = m + 1;
}
int solve_R(int curr) {
    if(curr >= n) return 0;
    if(curr == n-1) return 1;

    int &ret = dp_R[curr];
    if(ret != -1) return ret;

    m = 0;
    // for (int i = curr+1; i < n; i++) if(v[i] < v[curr]) m = max(m, solve_R(i));
    for (int i = n-1; i > curr; i--) if(v[i] < v[curr]) m = max(m, solve_R(i));
    return ret = m + 1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n; v.resize(n);
    memset(dp_L, -1, sizeof(dp_L)); memset(dp_R, -1, sizeof(dp_R));

    for (int i = 0; i < n; i++) cin >> v[i];

    int ans=0, flag = -1, temp;
    for (int i = 0; i < n; i++) ans = max(ans, solve_L(i) + solve_R(i));
    cout << ans - 1 << '\n';
}