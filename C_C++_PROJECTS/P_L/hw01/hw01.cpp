// #define DEBUG
#include <iostream>
#include <chrono>
#include <vector>
#include <ctime>

using namespace std;


int n;                          // 정수의 개수
int nums_copy[30];              // nums_copy[n] : n번째 입력받은 정수
vector<int> nums_vector;        // nums_vector[n] : n번째 입력받은 정수
bool isPrime[100001];           // primes[n] : true면 n은 소수
int max_n = -1;                 // 입력받은 정수의 최대값
int GCD = 1;                    // 최대 공약수

bool get_user_input(void){
    cin.clear();
    nums_vector.clear();
    int check = true;

    cout << ">> Input the number of numbers to process : ";
    cin >> n;                                               // 입력할 정수의 개수 입력
    
    if(n<=1 || n>=31){                                      // n의 범위(2~30) 검사
        return false;
    }

    max_n = -1;
    cout << ">> Input the numbers to be process : ";
    char check_char= ' ';
    int input_cnt=0;
    while(check_char == ' '){
        int temp_num;
        cin >> temp_num;
        if(temp_num<=0 || temp_num>=100001){
            check = false;
        }
        nums_vector.push_back(temp_num);
        nums_copy[input_cnt++] = temp_num;
        
        if(max_n <temp_num) max_n = temp_num;
        check_char = getchar();
    }
    if(nums_vector.size() != n){
        return false;
    }
    return check;
}

void sort_nums(void){
    int temp;
    for(int i=n-1; i>0; i--){
        for(int j=0; j<i; j++){
            if(nums_vector[j] > nums_vector[j+1]){
                temp = nums_vector[j];
                nums_vector[j] = nums_vector[j+1];
                nums_vector[j+1] = temp;
            }
        }
    }
}

void init_isPrime(void){
    for(int i=1; i<=100000; i++){
        isPrime[i] = true;
    }
}

void set_isPrime(void){
    for(int i=2; i<=50000; i++){
        if(isPrime[i]){
            for(int j=2*i; j<=100000; j+=i){
                isPrime[j] = false;
            }
        }
    }
}

int main(int argc, char const *argv[]){
    bool input_check = false;
    while(!input_check){
        input_check = get_user_input();
        if(!input_check){
            cout << ">> wrong input. Try again." << endl;
        }
    }
    
    #ifdef DEBUG
    cout << endl << "//>> n : " << n << endl;
    cout << "//>> nums_vector[] : ";
    for(int i=0; i<n; i++){
        cout << nums_vector[i] << " ";
    }
    cout << "//>> nums_copy[] : ";
    for(int i=0; i<n; i++){
        cout << nums_copy[i] << " ";
    }
    cout << endl;
    cout << "//>> max_n : " << max_n << endl;
    #endif

    chrono::system_clock::time_point StartTime = chrono::system_clock::now();

    sort_nums();                        // 입력받은 정수 정렬

    #ifdef DEBUG
    cout << "//>> sorted nums[] : ";
    for(int i=0; i<n; i++){
        cout << nums_vector[i] << " ";
    }
    cout << endl << endl;
    #endif

    init_isPrime();                     // 소수 배열 초기화
    set_isPrime();                      // 소수 구하기
    
    #ifdef DEBUG
    cout << "//>> set_isPrime ended." << endl;
    // int primeCnt =0;
    // cout << "//>> isPrime[] : ";
    // for(int i=2; i<=100000; i++){
    //     if(isPrime[i]){
    //         cout << i << " ";
    //         primeCnt++;
    //     }
    // }
    // cout << endl << "//>>prime nums : " << primeCnt << endl;
    #endif

    int div_check;
    for(int i=2; i<=max_n ; i++){               // 2~max_n
        if(isPrime[i]){                         // i가 소수면
            div_check = true;
            while(div_check){                   
                for(int j=0; j<n; j++){         // 입력받은 모든 정수들에 대해
                    if(nums_copy[j] % i != 0){       // 소수 i로 나누어 떨어지지 않으면
                        div_check = false;      // 다음 소수로
                        break;
                    }
                    nums_copy[j] /= i;               // 나누어 떨어지면 나눔
                }
                if(div_check) GCD *= i;         // 모든 정수를 나눌 수 있으면 최대공약수에 해당 소수 곱
            }
        }
    }

    cout << "GCD of input numbers is " << GCD << endl;      // 최대공약수 출력

    for(int i=0; i<n-1; i++){
        if(nums_vector[i] == nums_vector[i+1]) continue;                  // 중복되는 수는 건너뜀
        cout << "Number of prime numbers between " << nums_vector[i] << ", " << nums_vector[i+1] << ": ";
        int prime_cnt=0;
        for(int j=nums_vector[i]; j<=nums_vector[i+1]; j++){              // 두 정수 사이의 범위에서
            if(isPrime[j]) prime_cnt++;                     // 소수면 cnt+1
        }
        cout << prime_cnt << endl;
    }

    
    chrono::system_clock::time_point EndTime = chrono::system_clock::now();
    chrono::duration<double> DefaultSec = EndTime - StartTime;
    cout << "Total execution time using C++ is " << DefaultSec.count() * 1000 << "(milli sec)!" << endl;
    
    return 0;
}
