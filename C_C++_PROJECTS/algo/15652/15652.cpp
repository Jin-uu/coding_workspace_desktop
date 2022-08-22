#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n,m;
vector<int> v;

void dfs(int depth){
    if(depth == m) {
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
        cout << '\n';
        return;
    }

    for (int i = 1; i <= n; i++) {
        if(!v.empty() && v.back() > i) continue;
        v.push_back(i);
        dfs(depth+1);
        v.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;
    dfs(0);
}