#include <iostream>
#include <algorithm>
#define MAX 1000
using namespace std;

int n;
int ans[MAX+1];

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;

    ans[1] = 0; ans[2] = 1; ans[3] = 0; ans[4] = 1;
    for(int i=5; i<=n; i++) {
        ans[i] = 0;
        if(!ans[i-3] || !ans[i-1]) ans[i] = 1;
    }

    if(!ans[n]) cout << "SK";
    else cout << "CY";
}