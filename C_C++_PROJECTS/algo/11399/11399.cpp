#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n;
vector<int> p;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; i++) cin >> p[i]; 
    sort(p.begin(), p.end());
    int ans=0;
    for (int i = 0; i < p.size(); i++) ans += p[i]*(n-i);
    cout << ans;    
}