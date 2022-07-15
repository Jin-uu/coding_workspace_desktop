#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int t;

int solve(string s){
    string r = s; reverse(r.begin(), r.end());
    if(s == r) return 0;

    int ans = true, chk=false, s_flag = 0, r_flag = 0, len = s.length();
    for (int i = 0; i < len/2+1; i++){
        if(s[s_flag] == r[r_flag]) {s_flag++; r_flag++; continue;}
        if(chk) {ans=false; break;}
        if(s[s_flag] == r[r_flag+1]) {r_flag++; chk=true; continue;}
        ans=false; break;
    }
    if(ans) return 1;
    ans = true, chk=false, s_flag = 0, r_flag = 0; 
    for (int i = 0; i < len/2+1; i++){
        if(s[s_flag] == r[r_flag]) {s_flag++; r_flag++; continue;}
        if(chk) {ans=false; break;}
        if(s[s_flag+1] == r[r_flag]) {s_flag++; chk=true; continue;}
        ans=false; break;
    }
    if(ans) return 1;
    return 2;
}

int main(void){
    cin >> t;
    string temp_s;
    for (int i = 0; i < t; i++) {
        cin >> temp_s;
        cout << solve(temp_s) << endl;        
    }
}