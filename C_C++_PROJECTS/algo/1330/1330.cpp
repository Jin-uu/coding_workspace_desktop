#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int A,B;
    cin >> A >> B;

    if(A > B){ cout << ">" << endl; }
    else if(A < B) { cout << "<" << endl; }
    else cout << "==" << endl;

    return 0;
}