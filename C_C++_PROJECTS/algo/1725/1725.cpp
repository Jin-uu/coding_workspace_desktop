#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 100'000
using namespace std;

int n, tmp;
vector<int> v, lv, rv, st;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> tmp; v.push_back(tmp);
    }

    for(int i=0; i<n; i++) {
        while(!st.empty() && st.back() >= v[i]) st.pop_back();
        if(st.empty()) lv[i] = -1;
        else lv[i] = st.back();
        st.push_back(v[i]);
    }

}