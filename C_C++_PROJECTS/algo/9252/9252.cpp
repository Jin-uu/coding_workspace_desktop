#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MAX_N 1000
using namespace std;

string s1, s2;
int dp_tbl[MAX_N+1][MAX_N+1];

void tracker(int left, int right){
    if(left < 0 || right < 0) return;
    if(dp_tbl[left][right] == 0) return;

    if(s1[left] == s2[right]) {
        tracker(left-1, right-1);
        cout << s1[left];
        return;
    }
    int l = left <= 0 ? -1 : dp_tbl[left-1][right];
    int r = right <= 0 ? -1 : dp_tbl[left][right-1];
    if(l < r){
        tracker(left, right-1);
        return;
    }
    tracker(left-1, right);
    return;
}

int solve(int left, int right){
    if(left < 0 || right < 0) return 0;

    int &ret = dp_tbl[left][right];
    if(ret != -1) return ret;

    if(left <= 0 && right <= 0){
        if(s1[left] == s2[right]) return ret = 1;
        return ret = 0;
    }

    if(s1[left] == s2[right]){
        return ret = solve(left-1, right-1) +1;
    }
    return ret =  max(solve(left-1,right), solve(left,right-1));
}

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> s1 >> s2;

    memset(dp_tbl, -1, sizeof(dp_tbl));

    cout << solve(s1.length()-1, s2.length()-1) << '\n';
    tracker(s1.length()-1, s2.length()-1);
}