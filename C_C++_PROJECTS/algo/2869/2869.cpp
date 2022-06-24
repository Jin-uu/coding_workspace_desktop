#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int a, b, v;
    cin >> a >> b >> v;
    
    int ans=(v-a) / (a-b);
    if(((v-a) % (a-b)) != 0){
        ans += 2;
    }
    else ans++;

    cout << ans;
    return 0;
}