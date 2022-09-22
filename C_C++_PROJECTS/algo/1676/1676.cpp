#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int n, cnt_2, cnt_5, cnt_10;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n;
    int cpy;
    for (int i = 1; i <= n; i++) {
        cpy = i;
        while(cpy % 2 == 0) {
            cnt_2++;
            cpy /= 2;
        }
        cpy = i;
        while(cpy % 5 == 0) {
            cnt_5++;
            cpy /= 5;
        }        
    }
    cout << min(cnt_2, cnt_5) + cnt_10;
}