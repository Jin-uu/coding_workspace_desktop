#include <iostream>
#include <cstring>
#include <cmath>

#define MAX_N 100

using namespace std;

int n,ans_1, ans_2;
char MAP[MAX_N+1][MAX_N+1];
bool isChk[MAX_N+1][MAX_N+1];
int move_a[] = {-1, 1, 0, 0};
int move_b[] = {0, 0, -1, 1};

void solve_1(int a, int b, char clr){
    int next_a, next_b;
    for (int i = 0; i < 4; i++){
        next_a = a + move_a[i]; next_b = b + move_b[i];
        if(next_a < 0 || next_b < 0 || next_a >= n || next_b >= n) continue;
        if(isChk[next_a][next_b]) continue;
        if(MAP[next_a][next_b] == clr){
            isChk[next_a][next_b] = true;
            solve_1(next_a, next_b, clr);
        }
    }
}
void solve_2(int a, int b, char clr){
    int next_a, next_b;
    for (int i = 0; i < 4; i++){
        next_a = a + move_a[i]; next_b = b + move_b[i];
        if(next_a < 0 || next_b < 0 || next_a >= n || next_b >= n) continue;
        if(isChk[next_a][next_b]) continue;
        if(clr == 'R' || clr=='G'){
            if(MAP[next_a][next_b] == 'R' || MAP[next_a][next_b] == 'G'){
                isChk[next_a][next_b] = true;
                solve_2(next_a, next_b, clr);
            }
            continue;
        }        
        if(MAP[next_a][next_b] == clr){
            isChk[next_a][next_b] = true;
            solve_2(next_a, next_b, clr);
        }
    }
}

int main(void){
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> MAP[i][j];   
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(!isChk[i][j]){
                isChk[i][j] = true;
                solve_1(i, j, MAP[i][j]);
                ans_1++;
            }   
        }
    }
    memset(isChk, false, sizeof(isChk));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(!isChk[i][j]){
                isChk[i][j] = true;
                solve_2(i, j, MAP[i][j]);
                ans_2++;
            }   
        }
    }
    cout << ans_1 << ' ' << ans_2;
}