#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define MAX_N 9

using namespace std;

int MAP[MAX_N+1][MAX_N+1];
vector<pair<int,int>> mt;

pair<bool,int> isUniq(int r, int c){
    int cnt=0;
    for (int i = 0; i < 9; i++) {
        if(MAP[r][i] == 0) cnt++;
    }
    if(cnt==1) return {true,1};

    cnt=0;
    for (int i = 0; i < 9; i++) {
        if(MAP[i][c] == 0) cnt++;
    }
    if(cnt==1) return {true,2};

    cnt=0;
    for (int i = r/3 * 3; i < r/3 * 3 + 3; i++) {
        for (int j = c/3 * 3; j < c/3 * 3 + 3; j++) {
            if(MAP[i][j] == 0) cnt++;            
        }
    }
    if(cnt==1) return {true,3};

    return {false, 0};
}

void setUniq(int r, int c, int type){
    bool list[10];
    memset(list, false, sizeof(list));
    if(type == 1){
        for (int i = 0; i < 9; i++) {
            list[MAP[r][i]] = true;
        }
        for (int i = 1; i <= 9; i++){
            if(!list[i]) MAP[r][c] = i;
        }
        return;
    }

    if(type==2){
        for (int i = 0; i < 9; i++) {
            list[MAP[i][c]] = true;
        }
        for (int i = 1; i <= 9; i++){
            if(!list[i]) MAP[r][c] = i;
        }
        return;
    }

    if(type==3){
        for (int i = r/3 * 3; i < r/3 * 3 + 3; i++) {
            for (int j = c/3 * 3; j < c/3 * 3 + 3; j++) {     
                list[MAP[i][j]] = true;
            }
        }
        for (int i = 1; i <= 9; i++){
            if(!list[i]) MAP[r][c] = i;
        }
        return;
    }
}

void init_MAP(void){
    pair<bool, int> chk;
    bool flag;
    do {
        flag = false;
        for (int i = mt.size()-1; i >= 0; i--) {
            chk = isUniq(mt[i].first, mt[i].second);
            if(!chk.first) continue;
            setUniq(mt[i].first, mt[i].second, chk.second);
            mt.erase(mt.begin()+i);
            flag = true;
        } 
    }while(flag);
}

void __dbg_printMAP(void){
    for (int  i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << MAP[i][j] << " ";
        }
        cout << endl;
    }
}

bool isVal(int r, int c, int val){
    for (int i = 0; i < 9; i++) {
        if(i == c) continue;
        if(MAP[r][i] == val) return false;
    }
    for (int i = 0; i < 9; i++) {
        if(i == r) continue;
        if(MAP[i][c] == val) return false;
    }
    for (int i = r/3 * 3; i < r/3 * 3 + 3; i++) {
        for (int j = c/3 * 3; j < c/3 * 3 + 3; j++) {
            if(i == r && j == c) continue;
            if(MAP[i][j] == val) return false;            
        }
    }
    return true;
}

bool solve(int depth){
    if(depth == mt.size()) return true;
    for (int i = 1; i <= 9; i++) {
        if(isVal(mt[depth].first, mt[depth].second, i)){
            MAP[mt[depth].first][mt[depth].second] = i;
            if(solve(depth+1)) return true;
            MAP[mt[depth].first][mt[depth].second] = 0;
        }
    }
    return false;
}

int main(void){
    for (int  i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> MAP[i][j];
            if(MAP[i][j] == 0) {
                mt.push_back({i,j});
            }
        }
    }

    // init_MAP();
    solve(0);
    __dbg_printMAP();
}

