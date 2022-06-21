#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t;
    cin >> t;
    if(t <= 100 && t>=90) cout << "A" << endl;
    else if(t <= 89 && t>=80) cout << "B" << endl;
    else if(t <= 79 && t>=70) cout << "C" << endl;
    else if(t <= 69 && t>=60) cout << "D" << endl;
    else cout << "F" << endl;


    return 0;
}