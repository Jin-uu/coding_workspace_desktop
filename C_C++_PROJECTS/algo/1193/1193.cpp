#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int x;
    cin >> x;

    int cnt=0, flag=0;
    while(flag < x){
        flag += ++cnt;
    }

    int a=1+(flag-x); int b=cnt-(flag-x);

    if(cnt%2) cout << a << '/' << b << '\n';
    else cout << b << '/' << a << '\n';

    return 0;
}