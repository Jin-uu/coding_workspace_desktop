#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n,x;
    int min_ans = INT_MAX;
    int max_ans = -INT_MAX;
    cin >> n;
    for(int i=0; i<n ; i++) {
        cin >> x;
        min_ans = min(min_ans, x);
        max_ans = max(max_ans, x);
    }
    
    cout << min_ans << " " << max_ans;
    return 0;
}