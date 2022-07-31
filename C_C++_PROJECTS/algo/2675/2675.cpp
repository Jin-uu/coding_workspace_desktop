#include <iostream>
#include <cstring>
using namespace std;

int t, r;
string s;

void solve(void){
    cin >> r >> s;
    for (int i = 0; i < s.length(); i++) for (int j = 0; j < r; j++) cout << s[i];
}

int main(void){
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve(); cout << endl;
    }
}