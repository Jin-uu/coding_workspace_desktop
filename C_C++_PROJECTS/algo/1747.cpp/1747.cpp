#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int N;
int isPrime[1003334];

void set_isPrime(void){
    memset(isPrime, true, sizeof(isPrime));

    isPrime[0] = isPrime[1] = false;
    for(int i=2; i<=1003333; i++){
        if(!isPrime[i]) continue;
        for (int j = i+i; j <= 1003333; j+=i) {
            isPrime[j] = false;
        }
    }
}

bool isPaline(int n){
    string r = to_string(n);
    string l = r;
    reverse(l.begin(), l.end());
    if(r == l) return true;
    return false;    
}

int main(void){
    cin >> N;

    set_isPrime();

    while(1){
        if(isPrime[N] && isPaline(N)){
            cout << N ;
            return 0;
        }
        N++;
    }
}