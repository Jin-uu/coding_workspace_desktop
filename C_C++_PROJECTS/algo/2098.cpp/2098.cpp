#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define INF 1'987'654'321

using namespace std;

int N;
int W[16][16];
int dp[1<<16][16];      // dp[i][j] : 방문한 도시 : i, 현재 위치 :j일 떄 최소거리

void set_dp(){
    memset(dp,-1,sizeof(dp));
}

// visited : 방문한 도시, curr : 현재 방문할 도시 => 일떄 시작 도시로 가는 최단 거리
int get_dp(int visited, int curr){      
    visited |= (1<<curr);         // curr번 도시 마킹

    if(visited == (1<<N) -1){     // 모든 도시를 방문한 경우
        if(W[curr][0] != 0) return W[curr][0];      // 출발도시로 돌아갈 수 있는 경우 그 거리 반환
        return INF;                                 // 없는 경우 INF반환
    }

    int& ret = dp[visited][curr];
    if(ret != -1) return ret;

    ret = INF;
    for(int i=0; i<N; i++){                 // i는 다음 방문 도시
        if(i == curr) continue;             // 현재 도시 말고
        if((visited&(1<<i)) == 0){          // i번 도시를 방문하지 않은 경우
            if(W[curr][i] == 0) continue;   // curr -> i 길 없는 경우 continue
            ret = min(ret, get_dp(visited,i) + W[curr][i]);     // i도시로 가는 경우의 최소값 반영 갱신
        }
    }
    return ret;
}

int main(void){
    cin >> N;
    for(int i=0; i<N; i++) for(int j=0; j<N; j++) { cin >> W[i][j]; }

    set_dp();
    cout << get_dp(0,0) << endl;
}
