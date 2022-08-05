#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX_N 9
using namespace std;

int MAP[MAX_N+1][MAX_N+1];
vector<pair<int,int>> mt;

void __dbg_printMAP(void){
    for (int  i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << MAP[i][j] << "";
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
    string input;
    for (int  i = 0; i < 9; i++) {
        cin >> input;
        for (int j = 0; j < 9; j++) {
            MAP[i][j] = input[j] - '0';
            if(MAP[i][j] == 0) {
                mt.push_back({i,j});
            }
        }
    }

    solve(0);
    __dbg_printMAP();
}