#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define MAX_N 2000
using namespace std;

int n, m;
vector<int> nums;
vector<pair<int,int>> qs;
int dp_tbl[MAX_N+2][MAX_N+2];

bool solve(int left, int right){
    if(left >= right) return true;

    int &ret = dp_tbl[left][right];
    if(ret != -1) return ret;

    if(nums[left] == nums[right]) return ret = solve(left+1, right-1);
    return ret = false;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n; nums.resize(n+1);
    for (int i = 1; i <= n; i++) cin >> nums[i];

    cin >> m;
    int t_f, t_s;
    for (int i = 0; i < m; i++) {
        cin >> t_f >> t_s;
        qs.push_back({t_f, t_s});
    }
    
    memset(dp_tbl, -1, sizeof(dp_tbl));
    for (int i = 0; i < m; i++) cout << solve(qs[i].first, qs[i].second) << '\n';
}