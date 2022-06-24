#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;
    int shell=1, flag=1;
    while(flag < n){
        flag += (shell)*6;
        shell++;
    }

    cout << shell;
    return 0;
}