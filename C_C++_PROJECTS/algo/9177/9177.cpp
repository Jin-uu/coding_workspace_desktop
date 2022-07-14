#include <iostream>
#include <cstring>
#define MAX_N 200

using namespace std;

int n, s1_len, s2_len, tgt_len;
string s1, s2, tgt;
int dp_tbl[MAX_N+10][MAX_N+10];


bool solve(int left, int right){
    if(left + right == tgt_len) return true;

    int &ret = dp_tbl[left][right];
    if(ret != -1) return ret;

    int curr = left+right-1;
    if(tgt[curr+1] == s1[left]) if(solve(left+1, right)) return ret = true;
        
    if(tgt[curr+1] == s2[right]) if(solve(left, right+1)) return ret = true;
        
    return ret = false;
}

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s1 >> s2 >> tgt;
        s1_len = s1.length(); s2_len = s2.length(); tgt_len = tgt.length();
        memset(dp_tbl, -1, sizeof(dp_tbl));
        if(solve(0,0)) cout << "Data set " << i+1 <<": yes" << '\n';
        else cout << "Data set " << i+1 <<": no" << '\n';
    }
}