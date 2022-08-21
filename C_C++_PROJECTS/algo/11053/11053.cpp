#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define MAX_N 1'000
using namespace std;

int n;
int dp_tbl[MAX_N+1];
vector<int> v;

int solve(int curr){
    if(curr < 0) return 0;

    int &ret = dp_tbl[curr];
    if(ret != -1) return ret;
    
    int m=0;
    for (int i = curr-1; i >= 0; i--) if(v[i] < v[curr]) m = max(m, solve(i));
    return ret = m+1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n; v.resize(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    
    memset(dp_tbl, -1, sizeof(dp_tbl));
    int m = 0;
    for (int i = 0; i < n; i++) m = max(m, solve(i));    
    cout << m;
}