#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int x;
    cin >> x;

    for(int i=1 ; i<=9 ; i++){
        cout << x << " * " << i << " = " << x*i << endl;
    }

    return 0;
}