#include <bits/stdc++.h>
#define MAX_N
using namespace std;

int n, last;
vector<int> w;

void solve(void){
    sort(w.begin(),w.end());
    if(w[0] != 1) { last = 0; return;}
    last=1;
    for (int i = 1; i < n; i++){
        if(w[i] >= last+2) return;
        last += w[i];
    }
}
int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int temp_w;
    for (int i = 0; i < n; i++) {
        cin >> temp_w;
        w.push_back(temp_w);
    }
    solve();
    cout << last+1;
}