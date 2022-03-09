#define MAX 100000
#include <iostream>


using namespace std;

int n=-1, m=-1;
int MONEY[MAX+1];     // MONEY[n] : 그날 쓸 돈

bool isPos(int k){
    int cnt = 0;                        // 현재 인출 회수
    int curr_money = 0;                 // 현재 남은 돈
    for(int i=1; i<n+1; i++){
        if(MONEY[i] > k) return false;  // 그날 쓸 돈이 인출할 수 있는 금액보다 큰 경우 false
        if(curr_money < MONEY[i]){      // 현재 돈이 써야하는 금액보다 적으면
            curr_money = k;             // 돈 넣고 k만큼 인출
            cnt++;                      // 인출 회수 + 1
        }
        if(cnt > m) return false;       // 최대 인출 회수 초과시 false
        curr_money -= MONEY[i];         // 현재 돈에서 그날 쓸 돈 지출
    }
    return true;
}

int main(void){
    scanf("%d %d", &n, &m);

    int total=0;
    for(int i=1; i<n+1; i++){
        scanf("%d", &MONEY[i]);
        total += MONEY[i];
    }

    int least = total / m;

    int left = least;
    int right = total;
    int mid= (left+right)/2;
    int ans =-1;

    while(left <= right){
        mid = (left+right)/2;
        if(isPos(mid)){         // 중간이 가능하면
            right = mid-1;      // 중간의 왼쪽 탐색
            ans = mid;
        }
        else{                   // 중간이 불가능하면
            left = mid+1;       // 중간의 왼쪽 탐색
        }
    }

    printf("%d", ans);
}