// #define DEBUG

#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 1000

int n;                  // 입력할 정수의 개수 n
int A[MAX_N];           // 입력할 정수들을 담을 배열
int dp[MAX_N];          // dp[n] : A[n]을 마지막으로 하는 가장 긴 배열의 길이
int tracker[MAX_N];     // tracker[n] : A[n]을 포함하는 가장 긴배열의 바로 앞 정수의 index

void print_dp(void){    // debug
    cout << "dp[] : ";
    for(int i=0; i<n; i++){
        cout << dp[i] << "  ";                
    }
    cout << endl;
}
void print_tracker(void){    // debug
    cout << "tr[] : ";
    for(int i=0; i<n; i++){
        cout << tracker[i] << "  ";                
    }
    cout << endl;
}

void get_user_input(void){      // 입력받기
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> A[i];
    }
}

void set_dp(void){
    for(int i=0; i<n; i++){
        int tracker_index = i-1, max_length=-1, max_index=-1;
        while( tracker_index >= 0){                              // 앞 정수 탐색
            if(A[tracker_index] >= A[i]){                         // i번째 정수보다 크면 패스
                tracker_index--;
                continue;               
            }
            if(dp[tracker_index] > max_length){                 // 앞 배열 중 최대값 탐색
                max_length = dp[tracker_index];                 // 최대값 갱신
                max_index = tracker_index;                      // 최대값 갖는 index 갱신
            }
            tracker_index--;                                    // 다음 index로  
        }
        if(max_index < 0){                      // 앞 정수가 없는 경우
            tracker[i] = -1;                    // A[i]가 꼬리임
            dp[i] = 1;                          // 배열 길이 1
        }
        else{                                   // 앞 정수가 있는 경우
            tracker[i] = max_index;             // 앞 정수 index입력
            dp[i] = dp[max_index] + 1;
        }
        #ifdef DEBUG
        print_dp();
        print_tracker();
        cout << "-" << endl;
        #endif
    }
}

void get_ans(void){
    int MAX = -1, MAX_index =-1;
    for(int i=0; i<n; i++){             // 최대값 탐색
        if(MAX < dp[i]){                // 최대값 갱신
            MAX = dp[i];
            MAX_index = i;
        }    
    }
    cout << MAX << endl;                // 최대값 출
    
    vector<int> v;
    v.push_back(A[MAX_index]);
    while(tracker[MAX_index] >= 0){
        v.push_back(A[tracker[MAX_index]]);
        MAX_index = tracker[MAX_index];
    }

    for(int i=v.size()-1; i>=0; i--){
        cout << v[i] << " ";
    }    
}

int main(void){
    get_user_input();
    set_dp();
    get_ans();
}
