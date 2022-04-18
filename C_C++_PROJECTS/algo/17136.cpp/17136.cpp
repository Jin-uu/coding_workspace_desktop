#include <iostream>
#include <algorithm>

using namespace std;

int paper[10][10];
int color[6];
int ans=987654321;

void cover(int r, int c, int size){
    for(int i=r; i<r+size; i++){
        for(int j=c; j<c+size; j++){
            paper[i][j] = 0;
        }
    }
}
void decover(int r, int c, int size){
    for(int i=r; i<r+size; i++){
        for(int j=c; j<c+size; j++){
            paper[i][j] = 1;
        }
    }
}

void set_color(void){
    for (int i = 1; i <= 5; i++) {
        color[i] = 5;
    }    
}

bool is_full(void){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if(paper[i][j]==1){
                return false;
            }
        }        
    }
    return true;
}

int get_max_len(int r, int c){
    int bound = 5, len;
    bound = min(bound, min(10 - r+1, 10-c +1));

    bool check = true;
    for(len=2; len<=bound; len++){
        for(int i=r; i<r+len; i++){
            for(int j=c; j<c+len; j++){
                if(paper[i][j]==0) check = false;
            }            
        }
        if(!check){
            return len-1;
        }
        if(len == 5) return len;
    }
    
    return -1;
}
// 18 18
void dfs(int total_cnt) {
    if(is_full()){
        ans = min(ans, total_cnt);
    }
    if(total_cnt >= ans){
        return;
    }
    int target_r = 0, target_c = 0;

    for (int i = 0; i < 10; i++) {
        bool check = false;
        for (int j = 0; j < 10; j++) {
            if(paper[i][j] == 1){
                target_r = i;
                target_c = j;
                check = true;
                break;
            }
        }
        if(check) break;
    }

    for(int i=get_max_len(target_r, target_c); i>=1; i--){      // 가능한 최대 크기의 종이부터 1까지
        if(color[i] <= 0) continue;
        color[i]--;
        cover(target_r, target_c, i);
        dfs(total_cnt+1);
        color[i]++;
        decover(target_r,target_c, i);
    }
}

int main(void) {
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++) {
            cin >> paper[i][j];
        }
    }
    set_color();
    dfs(0);
    if(ans == 987654321){
        cout << -1 << endl;
    }
    else
        cout << ans <<endl;
}