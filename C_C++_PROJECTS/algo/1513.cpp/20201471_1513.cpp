#define DEBUG
#define DIV 1000007

#include <bits/stdc++.h>
using namespace std;

#define MAX 50

int n,m,c;
int c_loc[MAX+2][MAX+2];                  // c_loc[i][j]=n : n번째 오락실 좌표=i,j          
int dp[MAX+2][MAX+2][MAX+2][MAX+2];             // dp[i][j][n][l] : l번을 마지막으로 지나고 i,j위치이고 지나온 오락실 개수가 n개 일때의 경우의 수

int get_dp(int y, int x, int left, int last){      // last: 마지막으로 방문한 오락실, 남은 오락실 개수
    if(y<1 || x<1) return 0;

    if(y==1 && x==1){                // 시작 지점인 경우
        if(c_loc[1][1] && c_loc[1][1] < last && left==1){       // 시작지점에 오락실이 있고 last보다 작고 남은 오락실 1개인 경우
            return 1;
        }
        if(c_loc[1][1] ==0 && left==0){                             // 시작지점에 오락실이 없고 남은 오락실 0개인 경우
            return 1;
        }
        return 0;
    }

    // 시작 지점이 아닌 경우
    int &ret = dp[y][x][left][last];
    if(ret != -1){              // 이미 방문해서 값이 갱신 되었으면
        return ret;
    }

    ret=0;
    if(c_loc[y][x] == 0){       // x,y에 오락실이 없는 경우
        // ret = (ret + get_dp(y-1,x,left,last) + get_dp(y,x-1,left,last)) % DIV;
        ret = (ret + get_dp(y-1, x, left, last)) % DIV;
        ret = (ret + get_dp(y, x-1, left, last)) % DIV;
    }
    if(c_loc[y][x] != 0 && c_loc[y][x] < last && left != 0){        // 현 위치에 오락실이 있고 조건을 만족하는 경우
        // ret = (ret + get_dp(y-1,x,left-1,c_loc[y][x]) + get_dp(y,x-1,left-1,c_loc[y][x])) % DIV;
        ret = (ret + get_dp(y - 1, x, left-1, c_loc[y][x])) % DIV;
        ret = (ret + get_dp(y, x - 1, left-1, c_loc[y][x])) % DIV;
        // ret = (ret + get_dp(y - 1, x, c_loc[y][x], left-1)) % DIV;
        // ret = (ret + get_dp(y, x - 1, c_loc[y][x], left-1)) % DIV;
    }
    return ret;
}

int main(void){
    memset(dp,-1,sizeof(dp));
    cin >> n >> m >> c;
    for (int i = 1; i <= c; i++){
        int temp_i, temp_j;
        cin >> temp_i >> temp_j;
        c_loc[temp_i][temp_j] = i;
    }

    for (int i = 0; i <= c; i++){
        cout << get_dp(n,m,i,MAX+2) << " ";
    }
}