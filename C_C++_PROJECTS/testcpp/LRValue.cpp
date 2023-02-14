#include <iostream>

using namespace std;

void func_1(int a, int b) {
    a = 999;
    b = 999;
}

void func_2(int& a, int& b) {
    a = 999;
    b = 999;
}

int main(void) {
    int x=1, y=1;
    
    func_1(x, y);   // x=1, y=1
    
    func_2(x, y);   // x=999, y=999
}