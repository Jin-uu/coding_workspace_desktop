#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
bool isUs[10];
vector<int> in, v;
vector<vector<int>> ans;

void dfs(int depth){
    if(depth == m) {
        ans.push_back(v);
        return;
    }
    for (int i = 0; i < n; i++) {
        if(isUs[i]) continue;
        v.push_back(in[i]); isUs[i] = true;
        dfs(depth+1);
        v.pop_back(); isUs[i] = false;
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
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] << " ";
        }
        cout << '\n';
    }
}