#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;

    string s;
    for (int i = 0; i < t; i++){
        s.clear();
        cin >> s;
        int stack = 1, score = 0;
        for (int j = 0; j < s.size(); j++) {
            if(s[j] == 'O'){
                score += stack++;
            }
            else stack=1;
        }
        cout << score << '\n';        
    }
    

    return 0;
}