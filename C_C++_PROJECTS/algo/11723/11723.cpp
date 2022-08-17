#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX 20
using namespace std;

int m;
bool s[MAX+1];

int solve(string op, int x){
    if(op == "add"){
        s[x] = true;
        return -1;
    }
    if(op == "remove"){
        s[x] = false;
        return -1;
    }
    if(op == "check") return s[x];
    
    if(op == "toggle"){
        s[x] = !s[x];
        return -1;
    }
    if(op == "all"){
        for (int i = 1; i <= 20; i++)s[i] = true;
        return -1;
    }
    if(op == "empty"){
        memset(s, false, sizeof(s));
        return -1;
    }
    return -999;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> m;
    string t_op;
    int t_x, ret;
    for (int i = 0; i < m; i++) {
        cin >> t_op;
        if(t_op != "all" && t_op != "empty") cin >>t_x;
        ret = solve(t_op, t_x);
        if(ret == -1) continue;
        cout << ret << '\n';
    }
}