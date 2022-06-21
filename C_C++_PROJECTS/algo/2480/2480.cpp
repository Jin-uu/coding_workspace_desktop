#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int a, b, c;
    cin >> a >> b >> c;
    int ans = 0;
    if(a == b && b ==c){
        ans = 10000 + a*1000;
    }
    else if(a==b || b==c || c==a){
        if(a==b) ans = 1000 + a*100;
        else ans = 1000 + c*100;
    }
    else ans = max(a,max(b,c))*100;

    cout <<ans;

    return 0;
}