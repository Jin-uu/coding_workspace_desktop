#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MAX_N 1000
using namespace std;
typedef struct _ls{
    int len;
    string lcs;
} ls;

string s1, s2;
int dp_tbl[MAX_N+1][MAX_N+1];
string dp_str[MAX_N+1][MAX_N+1];

ls solve(int left, int right){
    if(left < 0 || right < 0) return {0,""};
    if(left <= 0 && right <= 0){
        if(s1[left] == s2[right]) return {1,s1[left]+""};
        return {0,""};
    }

    int &ret_i = dp_tbl[left][right];
    string &ret_s = dp_str[left][right];
    if(ret_i != -1) return {ret_i, ret_s};

    ls ctn, ctn1, ctn2;
    string s;
    if(s1[left] == s2[right]){
        ctn = solve(left-1, right-1);
        ret_i = ctn.len+1; ret_s = ctn.lcs + s1[left];
        return {ret_i, ret_s};
    }

    ctn1 = solve(left-1, right);
    ctn2 = solve(left, right-1);
    if(ctn1.len < ctn2.len){
        ret_i = ctn2.len; ret_s = ctn2.lcs;
        return {ret_i, ret_s};
    }
    ret_i = ctn1.len; ret_s = ctn1.lcs;
    return {ret_i, ret_s};
}

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> s1 >> s2;

    memset(dp_tbl, -1, sizeof(dp_tbl));

    cout << solve(s1.length()-1, s2.length()-1).len << '\n';
    cout << solve(s1.length()-1, s2.length()-1).lcs << '\n';
}