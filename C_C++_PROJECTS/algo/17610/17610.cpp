#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int k,sum, ans=0;
vector<int> w;
bool isPos[14][2600001];


void solve(int num, int weight){
    if(num > k) return;
    
    bool &ret = isPos[num][weight];
    if(ret) return;
    ret = true;

    solve(num+1, weight);
    solve(num+1, weight+w[num]);
    solve(num+1, abs(weight-w[num]));
}

int main(void){
    cin >> k;
    w.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> w[i];
        sum += w[i];
    }
    solve(0,0);
    for (int i = 0; i <= sum; i++) {
        if(!isPos[k][i]) ans++;
    }
    
    cout << ans;
}