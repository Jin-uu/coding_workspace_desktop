#define DEBUG

#include <iostream>
using namespace std;

#define MAX 300 // 구슬 최대 개수

int n, m;        // 구슬 개수, 그룹 개수
int B[MAX] = {}; // 구슬 숫자 담을 배열

bool isPOS(int k) { // 최대값:k일 때 구슬 분할 가능 여부
    int cnt = 0;
    int curr_idx =-1;
    int curr_sum =0;
    int curr_group_cnt =0;

    while(curr_group_cnt < m) {                     // 현재 묶은 그룹이 그룹 최대 개수를 넘지 않을 때 까지
        while(curr_sum + B[curr_idx+1] < k) {       // 다음 구슬을 더해도 최대값을 넘지 않을 때까지
            curr_sum += B[++curr_idx];              // 현재 그룹에 구슬 추가
        }
        curr_group_cnt++;                           // 묶기 완료되면 그룹 수 +1
    }
    if(curr_idx < n) return false;                  // 최대한 묶었는데도 구슬이 남은경우 false
    

}