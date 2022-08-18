#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int n;
vector<int> v,sv;
set<int> s;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n;
    int temp;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        v.push_back(temp);
        s.insert(temp);
    }
    set<int>::iterator iter;
    for (iter = s.begin(); iter != s.end(); iter++) sv.push_back(*iter);
    
    for (int i = 0; i < n; i++) cout << lower_bound(sv.begin(), sv.end(), v[i]) - sv.begin() << " ";
}