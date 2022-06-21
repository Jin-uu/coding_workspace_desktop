#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int h, m;
    cin >> h >> m;

    if(m >= 45){
        m -= 45;
    }
    else{
        if(h==0){
            h = 23;
            m = 60 -(45 - m);
        }
        else{
            h -= 1;
            m = 60 -(45 - m);
        }
    }

    cout << h << " " << m;


    return 0;
}