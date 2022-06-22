#include <bits/stdc++.h>

using namespace std;

bool v[10101];

int self(int n){
    int copy = n, cnt=1;
    while(copy >= 10){
        copy /= 10; cnt++;
    }
    int ans=n;
    for (int i = 0; i < cnt; i++) {
        ans += n % 10; n /= 10;
    }
    
    return ans;
}

void set_v(int n){
    while(n <= 10000){
        n = self(n);
        v[n] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    fill(v, v+10000, true);

    for (int i = 1; i <= 10000; i++) {
        if(v[i]) set_v(i);
    }

    for (int i = 1; i <= 10000; i++) {
        if(v[i]) cout << i << '\n';
    }

    return 0;
}