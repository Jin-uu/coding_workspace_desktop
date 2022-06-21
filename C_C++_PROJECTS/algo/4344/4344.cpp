#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    float c;
    cin >> c;
    for (int i = 0; i < c; i++) {
        float n, sum=0;
        cin >> n;
        vector<float> v;
        for (int j = 0; j < n; j++) {
            float s;
            cin >> s;
            v.push_back(s);
            sum += s;
        }
        float avr = sum/n, cnt=0;
        for (int j = 0; j < v.size(); j++) {
            if(v[j] > avr) cnt++;
        }
        float ans = cnt/n*100;
        cout << fixed;
        cout.precision(3);
        cout << ans << "%\n";        
    }

    return 0;
}