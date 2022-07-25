#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MAX_N 1000

using namespace std;

string s1, s2;
int dp_tbl[MAX_N+10][MAX_N+10];

int main(void){
    cin >> s1 >> s2;
    s1 = "0"+s1; s2 = "0"+s2;

    for (int i = 1; i <= s1.length(); i++) {
        for (int j = 1; j <= s2.length(); j++) {
            if(s1[i] == s2[j]){
                dp_tbl[i][j] =dp_tbl[i-1][j-1]+1;
            }
            else{
                dp_tbl[i][j] = max(dp_tbl[i-1][j], dp_tbl[i][j-1]);
            }
        }
    }
    cout << dp_tbl[s1.length()-1][s2.length()-1];
}



