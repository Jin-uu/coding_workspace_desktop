#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n,m;
vector<string> v1,v2, rst;

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    string temp;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        v1.push_back(temp);
    }
    for (int i = 0; i < m; i++) {
        cin >> temp;
        v2.push_back(temp);
    }
    
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    
    for (int  i = 0; i < v1.size(); i++){
        if(v2[lower_bound(v2.begin(), v2.end(), v1[i])-v2.begin()].compare(v1[i]) == 0) rst.push_back(v1[i]);
    }

    cout << rst.size() << '\n';
    for (int i = 0; i < rst.size(); i++){
        cout << rst[i] << '\n';
    }
}