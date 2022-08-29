#include <iostream>
#include <algorithm>
#include <queue>
#define MAX_N 10
using namespace std;
typedef struct _loc{
    int r;
    int c;
} loc;

typedef struct _state{
    loc red;
    loc blue;
    int move;    
} state;

int n,m;
loc f_red, f_blue, hole;
char board[MAX_N+1][MAX_N+1];
int move_r[] = {-1, 1, 0, 0};
int move_c[] = {0, 0, -1, 1};

state get_next_state(state s, int dir){
    loc next_red = s.red, next_blue = s.blue;

    bool flag = true;
    while(flag){
        if(board[next_red.r][next_red.c] == '.') {
            next_red.r += move_r[dir]; next_red.c += move_c[dir];
            continue;
        }
        if(board[next_blue.r][next_blue.c] == '.') {
            next_blue.r += move_r[dir]; next_blue.c += move_c[dir];
            continue;
        }
        if(board[next_red.r][next_red.c] == 'O') {
            next_red.r = -1; next_red.c = -1;
            continue;
        }
        if(board[next_blue.r][next_blue.c] == 'O') {
            next_blue.r = -1; next_blue.c = -1;
            continue;
        }        
        break;
    }
    return {next_red, next_blue, s.move+1};
}

int bfs(loc fr, loc fb, loc hole) {
    queue<state> q;
    q.push({fr, fb, 0});

    state cs, ns;
    while(!q.empty()){
        cs = q.front(); q.pop();

        for (int mov = 0; mov < 4; mov++) {
            ns = get_next_state(cs, mov);
            if(ns.red.r == -1 && ns.blue.r != -1)
                return ns.move;
            if(ns.blue.r == -1)
                continue;
            q.push(ns);
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[n][m];
            if(board[i][j] == 'R')  f_red = {i,j};
            if(board[i][j] == 'B')  f_blue = {i,j};
            if(board[i][j] == 'O')  hole = {i,j};
        }
    }

    cout << bfs(f_red, f_blue, hole);
    
    
}