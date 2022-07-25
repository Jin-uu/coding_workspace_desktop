#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>

#define MAX_N 200
#define MAX_K 1000

using namespace std;

int n, k, s, x, y;
int MAP[MAX_N+1][MAX_N+1];
queue<pair<int,pair<int,int>>> q;
int move_y[] = {-1, 1, 0, 0};
int move_x[] = {0, 0, -1, 1};

int main(void){
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            cin >> MAP[i][j];
        }
    }
    cin >> s >> y >> x;

    q.push({0,{x-1,y-1}});
    if(MAP[y-1][x-1] != 0){
        cout << MAP[y-1][x-1];
        return 0;
    }  
    MAP[y-1][x-1] = -1;

    int curr_x, curr_y, curr_d, next_x, next_y;
    pair<int,int> flag = {MAX_K+1, 0};
    while(!q.empty()){
        curr_y = q.front().second.second; curr_x = q.front().second.first; curr_d = q.front().first;
        q.pop();
        
        for (int i = 0; i < 4; i++){
            next_y = curr_y + move_y[i]; next_x = curr_x + move_x[i];
            
            if(next_y < 0 || next_x < 0 || next_y >=n || next_x >= n) continue;
            if(MAP[next_y][next_x] == -1) continue;
            if(MAP[next_y][next_x] == 0) {
                MAP[next_y][next_x] = -1;
                q.push({curr_d+1,{next_x, next_y}});
                continue;
            }
            if(flag.first > MAP[next_y][next_x]){
                flag.first = MAP[next_y][next_x];
                flag.second = curr_d+1;
            }
        }
        
        if(q.front().first == curr_d) continue;
        if(flag.first != MAX_K+1) break;
    }
    if(flag.second > s || flag.first == MAX_K+1) cout << 0;
    else cout << flag.first;
}

