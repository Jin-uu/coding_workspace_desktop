#define MAX 64
#include <iostream>
using namespace std;
char I[MAX][MAX];

bool isSimp(int x, int y, int height){
    char check = I[y][x];
    for(int i=0; i<height; i++){
        for (int j = 0; j < height; j++){
            if(I[y+i][x+j]==check) continue;
            return false;
        }
    }
    return true;
}

void quad_tree(int depth, int x, int y, int height){
    if(isSimp(x,y,height)){
        cout << I[y][x];
        return;
    }
    cout << "(";
    quad_tree(depth+1,x,y,height/2);                    // 좌측 상단
    quad_tree(depth+1,x+height/2,y,height/2);           // 우측 상단
    quad_tree(depth+1,x,y+height/2,height/2);           // 좌측 하단
    quad_tree(depth+1,x+height/2,y+height/2,height/2);  // 우측 하단
    cout << ")";
}


int main(void){
    int n;
    cin >> n;

    for(int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cin >> I[i][j];
        }
    }

    quad_tree(1,0,0,n);  

    return 0;
}