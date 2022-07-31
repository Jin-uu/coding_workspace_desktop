#include <iostream>
#include <cstring>
using namespace std;

int n, ans=0;
string s;

int main(void){
    cin >> n >> s;
    for (int i = 0; i < n; i++) ans += s[i] - '0';
    cout << ans;
}