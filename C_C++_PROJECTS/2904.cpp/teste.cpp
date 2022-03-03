#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define MAX = 1000000

using namespace std;

int aratos[500000] = {}; // 소수를 담을 배열

int main(int argc, char const *argv[]) {
    int n;               // 입력받을 정수의 개수
    cin >> n;            // 정수의 개수 입력
    vector<int> numbers; // 정수들을 담을 벡터

    int temp_num;                       // 정수 입력받기 위한 temp값
    int MAX_INT=1, R_MAX;               // MAX_INT : 입력받은 정수 중 최대값
    for (int i = 0; i < n; i++){        // n개의 정수 입력 받음
        cin >> temp_num;
        numbers.push_back(temp_num);
        if(temp_num > MAX_INT){
            MAX_INT = temp_num;
        }
    }
    R_MAX = MAX_INT/2;

    // // debug {
    // cout << "max : " << MAX_INT << endl;
    // cout << "root max : " << R_MAX << endl;
    // // }

    bool isPrime[R_MAX+1] ={};
    for(int i=2; i<=R_MAX; i++){
        isPrime[i] = true;  // 모두 소수로 가정
    }
    for(int i=2; i<=R_MAX; i++){
        if(isPrime[i]){     // 소수이면
            for(unsigned long j=i*i; j<=R_MAX; j+=i){
                isPrime[j] = false;
            }
        }
    }
    // // debug {
    // cout << "isPrime : ";
    // for(int i=2; i<R_MAX+1; i++){
    //     if(isPrime[i]) cout << i << " ";
    // }
    // cout << endl;
    // // }


    vector<int> aratos_n;
    int curr_idx = 0;       // 소수의 개수

    for (int i = 1; i <= R_MAX; i++){
         if (isPrime[i]){  
            aratos[curr_idx] = i;
            aratos_n.push_back(i);
            curr_idx++;
        } 
    }

    // // debug {
    // cout << "curr_idx : " << curr_idx << endl;
    // cout << "aratos : ";
    // for(int i=0; i<curr_idx; i++){
    //     cout << aratos[i] << " ";
    // }
    // cout << endl;
    // // }

    int res[curr_idx][n] = {};
    int sum_div[curr_idx] = {};
    double score = 1;
    int div_ctn;
    int curr_num;
    for (int i = 0; i < curr_idx; i++)
    { // i : 모든 소수에 대해 실행
        div_ctn = 0;
        for (int j = 0; j < n; j++)
        { // j : 모든 입력 정수에 대해 실행
            curr_num = numbers[j];
            div_ctn = 0;
            while (curr_num % aratos[i] == 0)
            {                          // 해당 소수 i로 정수가 나누어 떨어지면
                curr_num /= aratos[i]; // 해당 소수로 나누고
                div_ctn++;             // 카운트 +1
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
    int move_cnt = 0;
    for (int i = 0; i < curr_idx; i++)
    { // 모든 소수에 대해 실행
        eq_cnt = 0;
        for (int j = 0; j < n; j++)
        { // 모든 입력정수에 대해 실행
            if (res[i][j] < sum_div[i])
            {
                move_cnt += sum_div[i] - res[i][j];
            }
        }
        score = (score)*pow(aratos[i], sum_div[i]);
    }

    cout << score << " " << move_cnt << endl;

    return 0;
}
