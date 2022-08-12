#include <iostream>
#include <vector>
#include <sstream>
#include <limits.h>
#include <algorithm>
#define INF INT_MAX
#define INIT 100
#define MAX_N 500'000
using namespace std;

int n, m, i, j;
vector<int> brk;

bool isPos(int n){
    stringstream ss; string cnl; ss << n; ss >> cnl;
    for (i = 0; i < cnl.length(); i++) {
        for (j = 0; j < brk.size(); j++) {
            if((cnl[i] - '0') == brk[j]) return false;
        }
    }
    return true;
}

int get_digit(int input){
    stringstream ss; string cnl; ss << input; ss >> cnl;
    return cnl.length();
}

int lower_n(){
    int curr=n;
    while(curr >= 0){
        if(isPos(curr)) return get_digit(curr) + n - curr;
        curr--;
    }
    return INF;
}
int upper_n(){
    int curr=n;
    while(curr <= MAX_N*2+1){
        if(isPos(curr)) return get_digit(curr) + curr - n;
        curr++;
    }
    return INF;
}

int main(void){
    cin >> n >> m;
    brk.resize(m);
    for (i = 0; i < m; i++) cin >> brk[i];

    cout << min({lower_n(), upper_n(), abs(n - INIT)}) << endl;;
}



