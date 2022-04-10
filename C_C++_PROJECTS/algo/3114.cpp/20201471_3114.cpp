#include <iostream>

using namespace std;

int r,c;        // 세로, 가로 크기
int banana[1500][1500];
int apple[1500][1500];
int banana_sum[1500][1500];
int apple_sum[1500][1500];
int dp[1500][1500];

void init_dp(void){
    for(int i=0; i<r; i++){
        dp[i][0] = 0;
    }
    for(int j=0; j<c; j++){
        dp[0][j] = 0;
    }
}


int get_MAX_AaddB(int y, int x){
    int NORTH_WEST, NORTH, WEST;
    NORTH_WEST = dp[y-1][x-1];
    NORTH_WEST += banana_sum[y][x];
    NORTH_WEST += apple_sum[y][x];

    NORTH = dp[y-1][x];
    NORTH += apple_sum[y][x];

    WEST = dp[y][x-1];
    WEST += banana_sum[y][x];
    return max(NORTH_WEST, max(NORTH, WEST));
}

void set_dp(void){
    for (int i = 1; i < r; i++){
        for (int j = 1; j < c; j++){
            dp[i][j] = get_MAX_AaddB(i,j);
        }        
    }    
}

int main(void){
    cin >> r >> c;

    getchar();
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            char AorB = getchar();
            if(AorB == 'A'){
                int A;
                cin >> A;
                apple[i][j] = A;
                banana[i][j] = 0;
            }
            else{
                int B;
                cin >> B;
                apple[i][j] = 0;
                banana[i][j] = B;
            }
            getchar();
        }
    }

    apple_sum[0][0] = 0;
    banana_sum[0][0] = 0;
    for(int i=0; i<r; i++){
        apple_sum[i][0] = 0;
    }
    for(int j=0; j<c; j++){
        banana_sum[0][j] = 0;
    }
    for (int i = 1; i < r; i++){
        for (int j = 1; j < c; j++){
            apple_sum[i][j] = apple_sum[i][j-1] + apple[i][j-1];
            banana_sum[i][j] = banana_sum[i-1][j] + banana[i-1][j];
        }        
    }

    init_dp();
    set_dp();

    cout << dp[r-1][c-1];
    return 0;
}
