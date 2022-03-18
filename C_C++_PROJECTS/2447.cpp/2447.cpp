/* 2447 별 찍기 - 10 */

#include <iostream>

using namespace std;

#define MAX 6561        // 3^8

char star[MAX+1][MAX+1] = {' ',};
int N=0;

void init_star(int n){    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            star[i][j] = ' ';
        }
    }
}

void print_star(int n){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            printf("%c",star[i][j]);
        }
        printf("\n");
    }
}

void set_min_sqr(int y, int x){
    star[y][x] = '*';
    star[y][x+1] = '*';
    star[y][x+2] = '*';
    star[y+1][x] = '*';
    star[y+1][x+2] = '*';
    star[y+2][x] = '*';
    star[y+2][x+1] = '*';
    star[y+2][x+2] = '*';
}

void recursive_star(int n, int y, int x){     // 한 변의 길이가 n인 사각형 출력
    if(n == 3){
        set_min_sqr(y,x);
        // print_star(N);
        return;
    }
    recursive_star(n/3, y, x+n/3*0);
    recursive_star(n/3, y, x+n/3*1);
    recursive_star(n/3, y, x+n/3*2);
    recursive_star(n/3, y+n/3*1, x+n/3*0);
    recursive_star(n/3, y+n/3*1, x+n/3*2);
    recursive_star(n/3, y+n/3*2, x+n/3*0);
    recursive_star(n/3, y+n/3*2, x+n/3*1);
    recursive_star(n/3, y+n/3*2, x+n/3*2);
}

int main(void){
    scanf("%d", &N);
    init_star(N);
    recursive_star(N,1,1);
    print_star(N);
}