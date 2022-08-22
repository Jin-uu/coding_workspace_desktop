#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#define MAX_N 100'000
using namespace std;

int n;
int prt[MAX_N+1];
vector<int> v[MAX_N+1];
queue<int> q;

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    memset(prt, -1, sizeof(prt));
    int left,right;
    for (int i = 0; i < n; i++) {
        cin >> left >> right;
        v[left].push_back(right); v[right].push_back(left);
    }

    q.push(1);
    int cn, nn;
    while(!q.empty()){
        cn = q.front(); q.pop();
        for (int i = 0; i < v[cn].size(); i++) {
            nn = v[cn][i];
            if(prt[nn] != -1) continue;
            q.push(nn); prt[nn] = cn;
        }        
    }
    for (int i = 2; i <= n; i++) cout << prt[i] << '\n';
}