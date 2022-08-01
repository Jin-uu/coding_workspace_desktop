#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#define MAX_W 15000
#define MAX_N 30

using namespace std;

int n, t;
vector<int> w, tgt;
int isPos[MAX_N+1][MAX_W+1];

int solve(int depth, int weight){
    if(weight == 0) return true;
    if(weight < 0 || depth < 0 || weight > 15000) return false;
    
    int &ret = isPos[depth][weight];
    if(ret != -1) return ret;

    int curr = w[depth];
    if(solve(depth-1, weight) || solve(depth-1, abs(weight-curr)) || solve(depth-1, weight+curr))
        return ret = true;
    
    return ret = false;
}

int main(void){
    cin >> n;
    w.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    cin >> t;
    tgt.resize(t);
    for (int i = 0; i < t; i++) {
        cin >> tgt[i];
    }
    
    memset(isPos, -1, sizeof(isPos));
    for (int i = 0; i < t; i++) {
        cout << (solve(n-1, tgt[i]) ? "Y" : "N") << " ";
    }
}


