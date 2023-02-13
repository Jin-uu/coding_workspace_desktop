#include <iostream>

using namespace std;

int global_val=-1;

int& func1(int& a) {
    global_val = a;
    return a;
}

int main(void) {
    int val01 = 999;
    cout << "val01 : " << val01 << endl;
    cout << "global_val : " << global_val << endl;

    func1(val01);
    cout << "val01 : " << val01 << endl;
    cout << "global_val : " << global_val << endl;

    global_val = 777;
    cout << "val01 : " << val01 << endl;
    cout << "global_val : " << global_val << endl;


}

