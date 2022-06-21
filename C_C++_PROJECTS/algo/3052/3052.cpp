#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int x;
    set<int> s;

    for (int i = 0; i < 10; i++) {   
        cin >> x;
        x %= 42;
        s.insert(x);
    }

    cout << s.size();
    

    return 0;
}