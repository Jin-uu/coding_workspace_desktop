#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define MAX_H 60
using namespace std;
typedef struct _health{
    int h0;
    int h1;
    int h2;
    int depth;
} health;

int n;
bool dp_tbl[MAX_H+1][MAX_H+1][MAX_H+1];
vector<int> scv;
queue<health> q;

health next_health(int type, int ic0, int ic1, int ic2, int icdep){
    if(type == 0) return {ic0-9, ic1-3, ic2-1, icdep+1};
    if(type == 1) return {ic0-9, ic1-1, ic2-3, icdep+1};
    if(type == 2) return {ic0-3, ic1-9, ic2-1, icdep+1};
    if(type == 3) return {ic0-3, ic1-1, ic2-9, icdep+1};
    if(type == 4) return {ic0-1, ic1-9, ic2-3, icdep+1};
    if(type == 5) return {ic0-1, ic1-3, ic2-9, icdep+1};
    return {-1,-1,-1,-1};
}

int main() {
   ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n; scv.resize(3);
    scv[0] = scv[1] = scv[2] = 0;
    for (int i = 0; i < n; i++) {
        cin >> scv[i];
    }
    
    memset(dp_tbl, false, sizeof(dp_tbl));
    int c0, c1, c2, cdep;
    health nh;

    q.push({scv[0], scv[1], scv[2], 0});
    while(!q.empty()){
        auto[c0,c1,c2,cdep] = q.front(); q.pop();
        // c0 = q.front().h0; c1 = q.front().h1; c2 = q.front().h2; cdep = q.front().depth; q.pop();
        if(c0 <= 0 && c1 <=0 && c2 <=0){
            cout << cdep; return 0;
        }

        for (int dir = 0; dir < 6; dir++) {
            nh = next_health(dir,c0,c1,c2,cdep);
            if(nh.h0 < 0) nh.h0=0; if(nh.h1 < 0) nh.h1=0; if(nh.h2 < 0) nh.h2=0;
            if(dp_tbl[nh.h0][nh.h1][nh.h2]) continue;
            q.push(nh); dp_tbl[nh.h0][nh.h1][nh.h2] = true;
        }
    }   
}