#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int x,idx;
    int max_ans = -INT_MAX;
    for(int i=1; i<=9 ; i++) {
        cin >> x;
        if(max_ans < x){
            idx = i; max_ans = x;
        }
    }
    
    cout << max_ans << '\n' << idx;
    return 0;
}