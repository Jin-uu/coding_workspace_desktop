#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#define MAX_N 4000

using namespace std;

string s1,s2;
int dp_tbl[MAX_N+1][MAX_N+1];

int main(void){
    cin >> s1 >> s2;
    int ans=0;
    for (int i = 0; i < s1.length(); i++){
        if(s1[i] == s2[0]) dp_tbl[i][0] = 1;
    }
    for (int i = 0; i < s1.length(); i++){
        if(s1[0] == s2[i]) dp_tbl[0][i] = 1;
    }
    
    for (int i = 1; i < s1.length(); i++) {
        for (int j = 1; j < s2.length(); j++) {
            if(s1[i] == s2[j]) dp_tbl[i][j] = dp_tbl[i-1][j-1]+1;
            ans = max(ans, dp_tbl[i][j]);
        }
    }
    
    cout << ans;

}