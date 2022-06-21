#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n,x;
    cin >> n >> x;
    vector<int> v;
    int t;
    for (int i = 0; i < n; i++) {
        cin >> t;
        v.push_back(t);
    }

    for (int i = 0; i < n; i++) {
        if(v[i] < x) cout << v[i] << ' ';        
    }

    
    

    return 0;
}