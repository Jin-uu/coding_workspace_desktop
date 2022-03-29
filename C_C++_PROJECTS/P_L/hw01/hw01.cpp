#define DEBUG
#include <iostream>
#include <chrono>

using namespace std;


int n;                          // 정수의 개수
int nums[30], nums_copy[30];    // nums[n] : n번째 입력받은 정수
bool isPrime[100001];           // primes[n] : true면 n은 소수
int divs[100001];               // divs[n] : 입력 받은 정수들 소수n으로 나눈 몫의 합
int max_n = -1;                 // 입력받은 정수의 최대값
int GCD = 1;                    // 최대 공약수

bool get_user_input(void){
    cin.clear(); 
    int check = true;

    cout << ">> Input the number of numbers to process : ";
    cin >> n;                                               // 입력할 정수의 개수 입력
    
    if(n<=1 || n>=31){                                      // n의 범위(2~30) 검사
        return false;
    }

    max_n = -1;
    cout << ">> Input the numbers to be process : ";
    for(int i=0; i<n; i++){
        int temp_num = -1;
        cin >> temp_num;
        if(temp_num<=0 || temp_num>=100001){
            check = false;
        }
        nums[i] = temp_num;
        nums_copy[i] = temp_num;
        if(max_n < temp_num) max_n = temp_num;
        // cin.clear();
    }
    char end_check = getchar();
    if(end_check == ' '){
        #ifdef DEBUG
        cout << "1)end_check : ' '" << endl;
        #endif
        cin.ignore(1,'\n');
        check = false;
    }
    else if(end_check == '\n'){
        #ifdef DEBUG
        cout << "2)end_check : '\\n'" << endl;
        #endif
    }
    else{
        #ifdef DEBUG
        cout << "3)end_check : " << end_check << endl;
        #endif
        check = false;
    }
    return check;
}

void sort_nums(void){
    int temp;
    for(int i=n-1; i>0; i--){
        for(int j=0; j<i; j++){
            if(nums[j] > nums[j+1]){
                temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
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
    cout << "//>> nums[] : ";
    for(int i=0; i<n; i++){
        cout << nums[i] << " ";
    }
    cout << endl;
    cout << "//>> max_n : " << max_n << endl;
    #endif

    chrono::system_clock::time_point StartTime = chrono::system_clock::now();

    sort_nums();                        // 입력받은 정수 정렬

    #ifdef DEBUG
    cout << "//>> sorted nums[] : ";
    for(int i=0; i<n; i++){
        cout << nums[i] << " ";
    }
    cout << endl << endl;
    #endif

    init_isPrime();                     // 소수 배열 초기화
    set_isPrime();                      // 소수 구하기
    
    #ifdef DEBUG
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
        if(nums[i] == nums[i+1]) continue;                  // 중복되는 수는 건너뜀
        cout << "Number of prime numbers between " << nums[i] << ", " << nums[i+1] << ": ";
        int prime_cnt=0;
        for(int j=nums[i]; j<=nums[i+1]; j++){              // 두 정수 사이의 범위에서
            if(isPrime[j]) prime_cnt++;                     // 소수면 cnt+1
        }
        cout << prime_cnt << endl;
    }

    
    chrono::system_clock::time_point EndTime = chrono::system_clock::now();
    chrono::duration<double> DefaultSec = EndTime - StartTime;
    chrono::nanoseconds nano = EndTime - StartTime;
    chrono::microseconds micro = chrono::duration_cast<chrono::microseconds>(EndTime - StartTime);
    chrono::milliseconds mill = chrono::duration_cast<chrono::milliseconds>(EndTime - StartTime);
    cout << fixed;
    cout.precision(15);
    cout << "Total execution time using C++ is " << DefaultSec.count() << "(default)!" << endl;
    cout << "Total execution time using C++ is " << nano.count() << "(nano sec)!" << endl;
    cout << "Total execution time using C++ is " << micro.count() << "(micro sec)!" << endl;
    cout << "Total execution time using C++ is " << mill.count() << "(milli sec)!" << endl;
    
    return 0;
}
