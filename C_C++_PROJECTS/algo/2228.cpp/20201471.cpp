#include <iostream>
#include <algorithm>
#define MAX 100
#define MIN -32768*100
using namespace std;

int n,m;
int N[MAX+1]={};
int dp[MAX+1][MAX/2+1]={};
int dp_2[MAX+1][MAX/2+1]={};
bool isVisited[MAX+1][MAX/2+1]={};
bool isVisited_2[MAX+1][MAX/2+1]={};

int sumN(int start, int end){           // N[start]~N[end]의 총합 반환
    int sum =0;
    for(int i=start; i<=end; i++){
        sum += N[i];
    }
    return sum;
}

int getdp(int area, int groups){        // 1~area 까지 groups개의 구간으로 나눈 최대값
    if(groups <= 0) return 0;
    if(area < groups*2-1) return MIN;                       // 나눌 구간보다 정수개수가 적은 경우
    if(isVisited[area][groups]) return dp[area][groups];    // 이미 방문 했으면 그대로 반환    
    isVisited[area][groups] = true;                         // 방문
    int max_dp=MIN;
    for(int i=groups*2-1; i<=area; i++){
        max_dp = max(max_dp, getdp(i-2,groups-1)+sumN(i,area));
    }
    max_dp = max(max_dp, getdp(area-1, groups));
    dp[area][groups] = max_dp;
    return dp[area][groups];
}

int main(void){
    cin >> n >> m;
    for(int i=1; i<=n; i++){
        cin >> N[i];
    }

    for(int i=1; i<=n; i++){        // dp[i][0] 최소값으로 초기화
        dp[i][0] = MIN;
    }

    cout << getdp(n,m);
}