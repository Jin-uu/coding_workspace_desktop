#include <bits/stdc++.h>

using namespace std;

int opr(int x){
    if(x < 10) x *10;
    int t,o;
    t = x % 10;
    o = (x / 10 + x % 10) % 10;
    return t*10 + o;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, cnt=0;
    cin >> n;
    int next = n;
    do{
        next = opr(next); cnt++;
    }while(next != n);
    cout << cnt;
    
    return 0;
}