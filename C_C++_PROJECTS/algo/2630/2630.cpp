#include <iostream>
#define MAX_N 128
using namespace std;
int n;
bool MAP[MAX_N+1][MAX_N+1];

bool isPure(int tgt, int r, int c, int siz){
    for (int i = r; i < r+siz; i++)
        for (int j = c; j < c+siz; j++)
            if(MAP[i][j] != tgt) return false;
    return true;
}

int solve(int tgt, int r, int c, int siz){
    if(siz == 1) {
        if(MAP[r][c] == tgt) return 1;
        return 0;
    }
    int total=0;
    if(MAP[r][c] == tgt){
        if(isPure(tgt, r, c, siz)) return 1;
    }
    total += solve(tgt, r, c, siz/2);   
    total += solve(tgt, r+siz/2, c, siz/2);   
    total += solve(tgt, r, c+siz/2, siz/2);   
    total += solve(tgt, r+siz/2, c+siz/2, siz/2);
    return total;
}

int main(void){
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> MAP[i][j];

    cout << solve(0,0,0,n) << '\n';
    cout << solve(1,0,0,n) << '\n';
}