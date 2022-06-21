#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int h, m, t;
    cin >> h >> m >> t;

    int t_h = t / 60 % 24;
    int t_m = t % 60;

    if(m + t_m < 60){
        m += t_m;
    }
    else{
        if(h ==23){
            h = 0;
            m = t_m + m - 60;
        }
        else{
            h += 1;
            m = t_m + m - 60;
        }
    }

    if(h + t_h < 24){
        h += t_h;
    }
    else{
        h = t_h + h - 24;
    }

    cout << h << " " << m;

    return 0;
}