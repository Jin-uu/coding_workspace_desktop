// #define DEBUG


#include <iostream>
#include <map>

using namespace std;

#define MAX_N 50
#define MAX_COST 10000

bool isPrime[MAX_N * MAX_COST +1];                  // isPrime[n] = n의 소수 여부
long long dp[MAX_N * MAX_COST +1] = {0, };          // dp[k] = k를 만들 수 있는 합의 경우의 수
map<int,int> cost;                                  // cost[n] = 가격이 n인 사탕의 개수
int candy[MAX_N+1] ={0,};                           // candy[n] = n번째로 입력받은 사탕 가격
bool isVisited[MAX_COST+1] = {false, };             // 해당 가격의 사탕에 대해 계산 수행 했는지

void initPrime(){
    for(long long i=0; i<MAX_N * MAX_COST +1; i++){
        isPrime[i] = true;
    }
}

void getPrime(long long max){               // 1~max 까지의 소수 구하기
    initPrime();
    for(long long i=2; i<=max; i++){
        if(isPrime[i]){
            for(long long j=i*i; j<=max; j+=i){
                isPrime[j] = false;
            }
        }
    }
}

void printPrime(long long max){             // debug
    long long cnt=0;
    cout << "prime nums : " << endl;
    for(long long i=2; i<=max; i++){
        if(isPrime[i]){
            cout << i << "  ";
            cnt++;
        }
    }
    cout << endl << "total prime num's num : " << cnt << endl;
}

void printDp(long long max){                // debug
    cout << "dp : ";
    for(long long i=1; i<=max; i++){
        cout << dp[i] << " ";
    }
    cout << endl;
    
}

int main(void){
    int n;          // 사탕의 개수
    cin >> n;       // n 입력

    int temp_cost;                  // 입력받기 위한 temp 가격 
    long long total_sum=0;          // 사탕 가격의 총합

    for(int i=1; i<=n; i++){        // 사탕 n개의 가격 입력
        // cin >> temp_cost;           // i번째 사탕의 가격 입력받음
        scanf("%d", &temp_cost);    // i번째 사탕의 가격 입력받음
        cost[temp_cost]++;          // 입력받은 가격의 사탕개수 +1
        candy[i] = temp_cost;       // i번째 사탕의 가격 삽입
        total_sum += temp_cost;     // 합계에 추가
    }

    // cin.clear();

    #ifdef DEBUG
    // cout << "n : " << n << endl;
    printf("n : %d", n);
    // cout << "candy[] : " ;
    // for(int i=1; i<=n; i++){
    //     cout << candy[i] << " ";
    // }
    // cout << endl;
    // cout << "total_sum : " << total_sum << endl;
    #endif

    getPrime(total_sum);            // 1부터 총 합계까지 소수 구하기
    #ifdef DEBUG1
    printPrime(total_sum);
    #endif

    dp[0] = 1;
    for(int i=1; i<=n; i++){                // 모든 사탕들에 대해
        int curr_cost = candy[i];           // 현재 가격을 i번째 사탕 가격으로 설정
        if(curr_cost == 0) continue;        // 만약 0원이면 다음 사탕으로 건너뜀
        if(isVisited[curr_cost]) continue;  // 이미 계산된 가격의 사탕이면 건너뜀
        isVisited[curr_cost] = true;
        
        for(long long j=total_sum; j>=1; j--){              // total_sum부터 1까지에 대해
            for(int c=1; c<=cost[curr_cost]; c++){          // 동일 가격의 사탕들 일괄 계산
                if(j < curr_cost*c) break;                  // 현재 사탕의 가격 * 개수가 총 금액보다 큰 경우 break
                dp[j] += dp[j-curr_cost*c];
            }
        }
        #ifdef DEBUG
        // printDp(total_sum);
        #endif
    }

    long long ans=0;

    for(long long i=2; i<=total_sum; i++){
        if(!isPrime[i]) continue;   // 소수가 아니면 건너뜀
        ans += dp[i];
    }
    ans *= cost[0]+1;

    #ifdef DEBUG
    cout << endl << "ans : ";
    #endif

    cout << ans << endl;
}