#include <iostream>
#define MAX_N 100'000
using namespace std;

int n;
int bar[MAX_N+1];

int main(void){
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> bar[i];
    }

    int m = 0, ans = 0;
    for (int i = n - 1; i >= 0; i--){
        if(bar[i] > m){
            ans++;
            m = bar[i];
        }
    }

    cout << ans;
}