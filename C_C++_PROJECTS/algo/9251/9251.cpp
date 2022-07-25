#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MAX_N 1000

using namespace std;

string s1, s2;
int dp_tbl[MAX_N][MAX_N];

int solve(int left, int right){
    if(left < 0 || right < 0) return 0;
    if(left <= 0 && right <= 0){
        if(s1[left] == s2[right]) return 1;
        return 0;
    }

    int &ret = dp_tbl[left][right];
    if(ret != -1) return ret;

    if(s1[left] == s2[right]){
        return ret = solve(left-1, right-1) +1;
    }
    return ret =  max(solve(left-1,right), solve(left,right-1));
}

int main(void){
    cin >> s1 >> s2;

    memset(dp_tbl, -1, sizeof(dp_tbl));

    cout << solve(s1.length()-1, s2.length()-1);
}



