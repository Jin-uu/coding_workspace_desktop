#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    float n, s, max_s=0;
    vector<float> v;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> s;
        v.push_back(s);
        max_s = max(max_s, s);
    }

    for (int i = 0; i < v.size(); i++) {
        v[i] = v[i]/max_s*100;
    }

    float sum=0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    
    sum /= n;

    cout << sum;        

    return 0;
}