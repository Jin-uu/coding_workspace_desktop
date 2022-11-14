#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
vector<int> in, v;

void dfs(int depth){
    if(depth == m) {
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
        cout << '\n';
        return;
    }
    for (int i = 0; i < n; i++) {
        if(!v.empty() && v.back() > in[i]) continue;
        v.push_back(in[i]);
        dfs(depth+1);
        v.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    int tn;
    for (int i = 0; i < n; i++) {
        cin >> tn;
        in.push_back(tn);
    }
    sort(in.begin(), in.end());
    dfs(0);
}