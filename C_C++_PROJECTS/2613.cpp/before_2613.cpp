// #define DEBUG

#include <iostream>
using namespace std;

#define MAX 300 // 구슬 최대 개수

int n, m;        // 구슬 개수, 그룹 개수
int B[MAX] = {}; // 구슬 숫자 담을 배열

void printBGroups(int k){       // k일 때 최대 그룹의 구슬 정수 출력
    int left = 0;
    int right = 0;
    int curr_sum=0;
    for(int i=0; i<m; i++){
        if(n-right <= m-i){                         // 남은 구슬의 개수와 남은 그룹 개수가 동일한 경우
            for(int j=0; j<n-right; j++){
                cout << "1 ";
            }
            return;
        }
        while(curr_sum + B[right] <= k){            // 다음 구슬을 더해도 최대값을 넘지 않을 때까지
            if(right >= n-1) {                      // right가 마지막 구슬인 경우 break;
                right++;
                break;
            }
            curr_sum += B[right];                   // 현재 그룹에 구슬 추가
            right++;
        }
        cout << right - left << " ";                // 해당 그룹의 구슬 개수 출력
        left = right;                               // 다음 그룹 탐색
        curr_sum = 0;
    }
}

bool isPos(int k) {             // 최대값:k일 때 구슬 분할 가능 여부
    int cnt = 0;
    int curr_idx =-1;
    int curr_sum =0;
    int curr_group_cnt =0;

    while(curr_group_cnt < m) {                     // 현재 묶은 그룹이 그룹 최대 개수를 넘지 않을 때 까지
        curr_sum = 0;
        while(curr_sum + B[curr_idx+1] <= k) {      // 다음 구슬을 더해도 최대값을 넘지 않을 때까지
            curr_sum += B[++curr_idx];              // 현재 그룹에 B[curr_idx]구슬 추가
            if(curr_idx == n-1){                    // 구슬을 모두 묶은 경우
                return true;
            }
        }
        curr_group_cnt++;                           // 묶기 완료되면 그룹 수 +1
    }
    if(curr_idx <= n) return false;                 // 최대한 묶었는데도 구슬이 남은경우 false
}

int main() {
    #ifdef DEBUG
    cout << ">> 2613 <<" << endl;  
    #endif

    int max_B = -1;

    cin >> n;
    cin >> m;
    for(int i=0; i<n; i++){
        cin >> B[i];
        if(max_B < B[i]) max_B = B[i];  // 구슬의 최대값 갱신
    }

    #ifdef DEBUG
    // cout << "B : " << endl;
    // for(int i=0; i<n; i++){
    //     cout << B[i] << " ";
    // }
    // cout << endl;    
    #endif

    #ifdef DEBUG
    // cout << "isPos(16) : " <<  isPos(16) << endl;
    // cout << "isPos(17) : " <<  isPos(17) << endl;
    // cout << "isPos(18) : " <<  isPos(18) << endl;
    // cout << "isPos(19) : " <<  isPos(19) << endl;
    #endif

    int left = max_B;
    int right = 100 * MAX;          // 들어올 수 있는 구슬의 최대값 * 최대 개수
    int mid = -1;
    int ans = -1;

    while(left <= right){            // 이분탐색
        mid = (left + right) / 2;
        if(isPos(mid)){             // 중간 값이 가능하다면
            ans = mid;              // 정답 갱신
            right = mid-1;          // 중간값의 왼 쪽 탐색
        }
        else{
            left = mid+1;           // 중간값의 오른 쪽 탐색
        }
    }

    #ifdef DEBUG
    cout << "ans : ";
    #endif

    cout << ans << endl;
    printBGroups(ans);
    return 0;
}
