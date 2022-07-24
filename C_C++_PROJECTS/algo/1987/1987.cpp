#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
#define MAX 20

using namespace std;

int r,c,ans=0;
bool isPos[30];
char MAP[MAX+1][MAX+1];
int move_a[] = {-1, 1, 0, 0};
int move_b[] = {0, 0, -1, 1};

void dfs(int a, int b, int depth){    
    ans = max(ans, depth);

    int next_a, next_b, next_idx;
    for (int i = 0; i < 4; i++) {
        next_a = a + move_a[i]; next_b = b + move_b[i];
        if(next_a >= r || next_b>=c || next_a<0 || next_b<0) continue;
        next_idx = MAP[next_a][next_b] - 'A';
        if(isPos[next_idx]){
            isPos[next_idx] = false;
            dfs(next_a, next_b, depth+1);
            isPos[next_idx] = true;
        }
    }
}

int main(void){
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> MAP[i][j];
        }
    }
    clock_t start, finish;
    double duration;
    start = clock();
    fill(isPos, isPos+30, true);
    isPos[MAP[0][0] - 'A'] = false;
    dfs(0,0,0);
    cout << ans+1 << endl;
    finish = clock();
    duration = (double) (finish - start) / CLOCKS_PER_SEC;
    cout << duration << "(sec)" << endl;
}