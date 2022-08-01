#include <iostream>
#include <vector>
#define MAX_N 100
#define MAX_K 10000

using namespace std;

int n,k, curr;
int dp_tbl[MAX_K+1];
vector<int> coin;

void __dbg_print_dp(void){
    for (int i = 0; i <= k; i++) {
        cout << dp_tbl[i] << " ";
    }
    cout << endl;
}

int main(void){
    cin >> n >> k;
    coin.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> coin[i];
    }

    dp_tbl[0] = 1;
    for (int i = 0; i < coin.size(); i++) {
        for (int j = 1; j <= k; j++) {
            curr = j-coin[i] < 0 ? 0 : dp_tbl[j-coin[i]];
            dp_tbl[j] += curr;
        }
        __dbg_print_dp();
    }
    
    cout << dp_tbl[k] << endl;
}