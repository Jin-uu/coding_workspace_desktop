#include <iostream>

using namespace std;

int n, c, ans=0;

int main(void){
    cin >> n;
    for (int i = 0; i <= n; i++) {
        c = i;
        while(c > 0){
            if(c%10 != 0 && c % 10 % 3 == 0){
                ans++;
            }
            c /= 10;
        }
    }
    cout << ans;
}