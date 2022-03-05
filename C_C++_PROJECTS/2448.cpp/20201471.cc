#include <iostream>
#define MAX 3072
using namespace std;

char STARS[3072+1][3072*2];

void init_STARS(int height){
    for(int y=1; y<=height; y++){
        for(int x=1; x<height*2; x++){
            STARS[y][x] = ' ';
        }
    }    
}

void print_stars(int height){
    for(int y=1; y<=height; y++){
        for(int x=1; x<height*2; x++){
            cout << STARS[y][x];
        }
        cout << endl;
    }    
}

void set_min_triangle(int x, int y){
    STARS[y][x] = '*';
    STARS[y+1][x-1] = '*';
    STARS[y+1][x+1] = '*';
    STARS[y+2][x-2] = '*';
    STARS[y+2][x-1] = '*';
    STARS[y+2][x] = '*';
    STARS[y+2][x+1] = '*';
    STARS[y+2][x+2] = '*';
}

void devide(int x, int y, int height){  // (x,y) : 삼각형의 윗 꼭짓점 좌표, height : 높이
    if(height == 3){
        set_min_triangle(x,y);
    }
    else{
        devide(x,y,height/2);               // 상단 삼각형 그리기
        devide(x-height/2,y+height/2,height/2);      // 좌측하단 삼각형 그리기
        devide(x+height/2,y+height/2,height/2);      // 우측하단 삼각형 그리기
    }

}

int main(void){
    int n;      // 전체 삼각형의 높이 (3×2^k) (k:0~10)
    cin >> n;   // 입력

    init_STARS(n);
    devide(n,1,n);
    print_stars(n);

    return 0;
}