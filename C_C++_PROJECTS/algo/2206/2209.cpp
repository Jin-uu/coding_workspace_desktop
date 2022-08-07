#include <iostream>
#include <queue>
#include <algorithm>
#include <limits.h>
#include <cstring>

#define MAX_N 1000
#define INF INT_MAX
using namespace std;

typedef struct _track {
    int r;
    int c;
    int depth;
    bool isBrk;
} track;

int n, m, ans = INF;
int MAP[MAX_N+1][MAX_N+1];
bool chk_brk[MAX_N+1][MAX_N+1];
bool chk_nbrk[MAX_N+1][MAX_N+1];
int move_r[] = {-1, 1, 0, 0};
int move_c[] = {0, 0, -1, 1};
queue<track> q;

int solve() {
    chk_nbrk[0][0] = true; q.push({0,0,1,false});
    track curr_node;
    int next_r, next_c;
    while (!q.empty()) {
        curr_node = q.front(); q.pop();
        if(curr_node.r == n-1 && curr_node.c == m-1) return curr_node.depth;

        for (int i = 0; i < 4; i++) {
            next_r = curr_node.r + move_r[i]; next_c = curr_node.c + move_c[i];
            bool &chk = (curr_node.isBrk ? chk_brk[next_r][next_c] : chk_nbrk[next_r][next_c]);

            if(next_r < 0 || next_c < 0 || next_r >= n || next_c >= m) continue;
            if(chk) continue;

            if(MAP[next_r][next_c] == 0){
                q.push({next_r, next_c, curr_node.depth+1, curr_node.isBrk});
                chk = true;
                continue;
            }

            if(MAP[next_r][next_c] == 1 && curr_node.isBrk==false){
                q.push({next_r, next_c, curr_node.depth+1, true});
                chk = true;
                continue;
            }          
        }
    }    

    return -1;
}

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);    
    cin >> n >> m;
    string temp;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        for (int j = 0; j < m; j++){
            MAP[i][j] = temp[j] - '0';
        }
    }

    cout << solve() << '\n';
}