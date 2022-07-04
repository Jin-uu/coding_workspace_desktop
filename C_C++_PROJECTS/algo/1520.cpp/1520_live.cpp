#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX_N 500

using namespace std;

int M,N;
int MAP[MAX_N+10][MAX_N+10];
int dp[MAX_N+10][MAX_N+10];

int dfs(int r, int c){
    if(r == M-1 && c == N-1) return 1;                  // 목적지 도착 검사
    if(r < 0 || c < 0 || r >= M || c >= N) return 0;    // MAP 넘어갔는지 검사

    int &ret = dp[r][c];
    if(ret != -1) return ret;   // 메모이제이션

    int sum=0;
    // 상
    if(MAP[r][c] > MAP[r-1][c]) sum += dfs(r-1,c);
    // 하
    if(MAP[r][c] > MAP[r+1][c]) sum += dfs(r+1,c);    
    // 좌
    if(MAP[r][c] > MAP[r][c-1]) sum += dfs(r,c-1);    
    // 우
    if(MAP[r][c] > MAP[r][c+1]) sum += dfs(r,c+1);

    return ret = sum;
}

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> M >> N;

    for (int i = 0; i < M; i++) for (int j = 0; j < N; j++) cin >> MAP[i][j];
    
    memset(dp, -1, sizeof(dp));
    cout << dfs(0,0);
}