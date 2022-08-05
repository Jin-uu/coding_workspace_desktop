#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <time.h>
#define MAX 110'00
typedef unsigned long long ll;

int dr=2,dc=3;

using namespace std;

ll solve_1_arr[MAX+1][MAX+1];
ll solve_2_arr[MAX+1][MAX+1];

double td_result[10][10];
double bu_result[10][10];
int flag[] = {1,2,3,5,10,100};

ll top_down(int r, int c){
    if(r < 0 || c < 0) return 0;
    if(r < dr || c < dc) return 1;

    ll &ret = solve_1_arr[r][c];
    if(ret != -1) return ret;

    return ret = top_down(r-dr+1, c-dc+1) + top_down(r-dr, c-dc);
}

void bottom_up(int r, int c) {
    for (int i = 0; i <= r; i++) {
        for (int j = 0; j < dc; j++) {
            solve_2_arr[i][j] = 1;
        }
    }
    for (int i = 0; i < dr; i++) {
        for (int j = 0; j <= c; j++) {
            solve_2_arr[i][j] = 1;
        }
    }
    
    for (int i = dr; i <= r; i++) {
        for (int j = dc; j <= c; j++) {
            solve_2_arr[i][j] = solve_2_arr[i-dr+1][j-dc+1] + solve_2_arr[i-dr][j-dc];
        }
    }
}

void get_result(int a, int b){
///////////////////////////////////////////////////////////////
    cout << "=========================================" << endl;
    cout << "dr : " << dr << ", dc : " << dc << endl;
    cout << "=========================================" << endl;
///////////////////////////////////////////////////////////////
    clock_t start, end;
    double result;
    start = clock();

    memset(solve_1_arr, -1, sizeof(solve_1_arr));
    cout << "top_down :" << top_down(MAX, MAX) << endl;

    end = clock();
    result = (double) (end - start);
    cout << "time : " << result << "(ms)" << endl;

    td_result[a][b] += result;

    cout << "-----------------------------------------" << endl;
///////////////////////////////////////////////////////////////

    clock_t start_2, end_2;
    double result_2;
    start_2 = clock();

    bottom_up(MAX, MAX);
    cout  << "bottom_up : " << solve_2_arr[MAX][MAX] << endl;

    end_2 = clock();
    result_2 = (double) (end_2 - start_2);
    cout << "time : " << result_2 << "(ms)" << endl;
    
    bu_result[a][b] += result_2;
///////////////////////////////////////////////////////////////

    cout << "=========================================" << endl;

}

void print_result(){
    cout << "=========================================" << endl;
    cout << "td_result" << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cout << td_result[i][j] / 3 << " ";
        }
        cout << endl;
    }
    cout << "=========================================" << endl;
    cout << "bu_result" << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cout << bu_result[i][j] / 3 << " ";
        }
        cout << endl;
    }
    
}

int main(){
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if(i==0 && j==0) continue;
            dr = flag[i]; dc = flag[j];
            for (int k = 0; k < 3; k++) {
                get_result(i,j);
            }
        }
    }

    print_result();
    

}