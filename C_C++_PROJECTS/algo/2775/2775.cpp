#include <bits/stdc++.h>

using namespace std;

int ap[15][15];

void init(void){
    memset(ap, -1, sizeof(ap));
    for (int i = 1; i < 15; i++) {
        ap[0][i] = i;
    }    
}

int solve(int k, int n){
    if(ap[k][n] != -1) return ap[k][n];
    int cnt=0;
    for(int i=1; i<=n; i++){
        cnt += solve(k-1, i);
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t, k ,n;
    cin >> t;

    init();
    for (int i = 0; i < t; i++) {
        cin >> k >> n;
        cout << solve(k,n) << '\n';
    }
    

    return 0;
}