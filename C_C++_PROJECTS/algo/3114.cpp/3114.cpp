// #define DEBUG
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
    // for (int i = 0; i < y; i++){
    //     NORTH_WEST += banana[i][x];
    // }
    NORTH_WEST += banana_sum[y][x];
    // for (int j = 0; j < x; j++){
    //     NORTH_WEST += apple[y][j];
    // }
    NORTH_WEST += apple_sum[y][x];

    NORTH = dp[y-1][x];
    // for (int j = 0; j < x; j++){
    //     NORTH += apple[y][j];
    // }
    NORTH += apple_sum[y][x];

    WEST = dp[y][x-1];
    // for (int i = 0; i < y; i++){
    //     WEST += banana[i][x];
    // }
    WEST += banana_sum[y][x];

    #ifdef DEBUG
    cout << NORTH_WEST << ",    " << NORTH << ",    " << WEST ;
    cout << " / max : " <<max(NORTH_WEST, max(NORTH, WEST)) << endl;
    #endif
    return max(NORTH_WEST, max(NORTH, WEST));
}

void set_dp(void){
    for (int i = 1; i < r; i++){
        for (int j = 1; j < c; j++){
            dp[i][j] = get_MAX_AaddB(i,j);
        }        
    }    
}

void _debug_print_dp(void){
    cout << "dp[][] : " << endl;
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            cout << dp[i][j] << "   ";
        }        
        cout << endl;
    }    
}

int main(void){
    cin >> r >> c;
    #ifdef DEBUG
    cout << "r,c : ";
    cout << r << ", " << c << endl;
    #endif

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
    

    
    #ifdef DEBUG
    cout << "apple[][] : "<< endl;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cout << apple[i][j] << "    ";
        }
        cout << endl;
    }
    cout << "apple_sum[][] : "<< endl;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cout << apple_sum[i][j] << "    ";
        }
        cout << endl;
    }
    cout << "banana[][] : "<< endl;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cout << banana[i][j] << "    ";
        }
        cout << endl;
    }
    cout << "banana_sum[][] : "<< endl;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cout << banana_sum[i][j] << "    ";
        }
        cout << endl;
    }
    #endif

    init_dp();
    #ifdef DEBUG
    _debug_print_dp();
    #endif

    set_dp();

    cout << dp[r-1][c-1];
    return 0;
}
