#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 100'000
using namespace std;

int n, tmp;
long long ans = -1;
vector<int> v,lst, rst;
int lv[MAX+1];
int rv[MAX+1];

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> tmp; v.push_back(tmp);
    }

    for(int i=0; i<n; i++) {
        while(!lst.empty() && v[lst.back()] >= v[i]) lst.pop_back();
        if(lst.empty()) lv[i] = -1;
        else lv[i] = lst.back();
        lst.push_back(i);
    }

    for(int i=n-1; i>=0; i--) {
        while(!rst.empty() && v[rst.back()] >= v[i]) rst.pop_back();
        if(rst.empty()) rv[i] = n;
        else rv[i] = rst.back();
        rst.push_back(i);
    }

    for(int i=0; i<n; i++) ans = max(ans, (long long)(rv[i]-lv[i] - 1)*(long long)v[i]);

    cout << ans;
}