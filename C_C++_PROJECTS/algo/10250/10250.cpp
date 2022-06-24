#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t;
    cin >> t;

    int h,w,n, flr, addr;
    for (int i = 0; i < t; i++) {
        cin >> h >> w >> n;
        flr = n % h; addr = n / h + 1;
        // cout << flr << " " << addr << '\n';

        if(flr != 0) {
            cout << flr << "";    
        }
        else{
            cout << h << ""; addr--;
        }
        if(addr < 10) cout << 0 << addr << '\n';
        else cout << addr << '\n';
    }

    return 0;
}