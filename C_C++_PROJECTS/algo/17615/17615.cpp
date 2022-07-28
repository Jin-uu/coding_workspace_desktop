#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <cmath>
#define MAX_N 500'000
#define INF INT_MAX

using namespace std;

int n, ans = INF, flag, cnt;
vector<char> ball;

int main(void){
    cin >> n;
    ball.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> ball[i];
    }
    
    // move blue to left
    flag=0, cnt=0;
    while(ball[flag] == 'B') flag++;
    for (int i = flag; i < ball.size(); i++) {
        if(ball[i] == 'B') cnt++;
    }
    ans = min(ans, cnt);

    // move blue to right
    flag=ball.size()-1, cnt=0;
    while(ball[flag] == 'B') flag--;
    for (int i = flag; i >= 0; i--) {
        if(ball[i] == 'B') cnt++;
    }
    ans = min(ans, cnt);

    // move red to left
    flag=0, cnt=0;
    while(ball[flag] == 'R') flag++;
    for (int i = flag; i < ball.size(); i++) {
        if(ball[i] == 'R') cnt++;
    }
    ans = min(ans, cnt);  

    // move red to right
    flag=ball.size()-1, cnt=0;
    while(ball[flag] == 'R') flag--;
    for (int i = flag; i >= 0; i--) {
        if(ball[i] == 'R') cnt++;
    }
    ans = min(ans, cnt);
    
    cout << ans << endl;
}