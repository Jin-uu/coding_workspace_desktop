#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int n;
void solve(int n){
    string s1, s2;
    s1 = s2 = to_string(n);
    reverse(s2.begin(), s2.end());
    if(s1 == s2){
        cout << "yes" << '\n'; return;
    }
    cout << "no" << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    while(1){
        cin >> n;
        if(n == 0) break;
        solve(n);
    }
}