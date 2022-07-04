#include <bits/stdc++.h>
#define MAX_N 500
#define INF INT_MAX

using namespace std;

int M, N;
int map_arr[MAX_N+2][MAX_N+2];
int dp[MAX_N+2][MAX_N+2];
int move_r[] = {-1, 1, 0, 0};
int move_c[] = {0, 0, -1, 1};

int dfs(int r, int c){
    if(r < 0 || c < 0 || r >= M || c >= N) return 0;
    if(r == M-1 && c == N-1) return 1;

    int &ret = dp[r][c];
    if(ret != -1) return ret;

    int sum=0;
    for (int i = 0; i < 4; i++) {
        int next_r = r + move_r[i];
        int next_c = c + move_c[i];
        if(map_arr[next_r][next_c] < map_arr[r][c]) sum += dfs(next_r, next_c);
    }
    return ret = sum;
}

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> M >> N;

    for (int i = 0; i < M; i++) for (int j = 0; j < N; j++) cin >> map_arr[i][j];

    memset(dp, -1, sizeof(dp));

    cout << dfs(0,0);
}