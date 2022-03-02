#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(int argc, char const *argv[]) {
    int n;              // 입력받을 정수의 개수

    // cout << "n :";
    cin >> n;           // 정수의 개수 입력

    // // debug{
    // cout << "n : " << n << '\n';
    // // }

    vector<int> numbers;            // 정수들을 담을 벡터

    int temp_num;                   // 정수 입력받기 위한 temp값
    for (int i = 0; i < n; i++)     // n개의 정수 입력 받음
    {
        cin >> temp_num;
        numbers.push_back(temp_num);
    }

    int MAX, R_MAX;         // MAX : 입력받은 정수 중 최대값
    MAX = *max_element(numbers.begin(), numbers.end());
    R_MAX = MAX / 2;      // R_MAX : 최대값에 루트씌움 -> /2 로 수정

    // // // debug {
    // cout << "max : " << MAX << endl;
    // cout << "root max : " << R_MAX << endl;
    // // // }

    int aratos[R_MAX] = {};                  // 소수를 담을 배열
    aratos[0] = 2;
    bool check = true;
    int curr_idx = 1;                       // 소수의 개수

    for(int i=3; i<R_MAX; i++){             // i가 소수인지 검사
        check = true;
        for(int j=0; j < curr_idx; j++){                    // aratos의 모든 인자에 대해
            if(i%aratos[j]==0){                             // 나누어 떨어지는 경우 : i는 소수아님
                check = false;                              // 따라서 aratos에 추가 안함
                break;            
            }
        }
        if(check){            
            aratos[curr_idx++] = i;                          // 검사에 통과했으면 추가
        }
    }

    // // // debug {
    // cout << "curr_idx : " << curr_idx << endl;
    // cout << "aratos : ";
    // for(int i=0; i<curr_idx; i++){
    //     cout << aratos[i] << " ";
    // }
    // cout << endl;
    // // // }

    int res[curr_idx][n]={};
    int sum_div[curr_idx]={};
    int score=1;
    int div_ctn;
    int curr_num;
    for(int i=0; i<curr_idx; i++){                  // i : 모든 소수에 대해 실행
        div_ctn=0;
        for(int j=0; j<n; j++){                     // j : 모든 입력 정수에 대해 실행
            curr_num = numbers[j];
            div_ctn =0;
            while(curr_num % aratos[i] == 0){       // 해당 소수 i로 정수가 나누어 떨어지면
                curr_num /= aratos[i];              // 해당 소수로 나누고
                div_ctn++;                          // 카운트 +1
            }
            res[i][j] = div_ctn;
            sum_div[i] += div_ctn;
        }
        sum_div[i] /= n;
    }

    // // debug{
    // cout << "res : " << endl;
    // for(int i=0; i<curr_idx; i++){
    //     for(int j=0; j < n; j++){
    //         cout << res[i][j] << ",";
    //     }
    //     cout << endl;
    // }
    
    // cout << "sum_div : " << endl;
    // for(int j=0; j<curr_idx; j++){
    //     cout << sum_div[j] << ",";
    // }
    // cout << endl;
    // //}

    int eq_cnt;
    int move_cnt=0;
    // for(int i=0; i<curr_idx; i++){          // 모든 소수에 대해 실행
    //     eq_cnt=0;
    //     if(sum_div[i]!=0){
    //         for(int j=0; j<n; j++){             // 모든 입력정수에 대해 실행
    //             if(res[i][j] == sum_div[i]){    // 인수가 목표랑 동일하면
    //                 eq_cnt++;                   // +1
    //             }
    //         }
    //         move_cnt += (n - eq_cnt - 1);
    //     }
    //     score *= pow(aratos[i], sum_div[i]);
    // }
    for(int i=0; i<curr_idx; i++){          // 모든 소수에 대해 실행
        eq_cnt=0;
        if(sum_div[i]!=0){
            for(int j=0; j<n; j++){             // 모든 입력정수에 대해 실행
                eq_cnt += abs(res[i][j]-sum_div[i]); 
            }
            move_cnt += eq_cnt/2;
        }
        score *= pow(aratos[i], sum_div[i]);
    }

    cout << score << " " << move_cnt << endl;


    return 0;
}
