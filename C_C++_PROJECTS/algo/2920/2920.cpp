#include <iostream>
#define MAX_N 8
using namespace std;

int note[MAX_N+1];
bool chk;

int main(void){
    for (int i = 0; i < 8; i++) cin >> note[i];
    
    chk = true;
    for (int i = 0; i < 8; i++){
        if(note[i] != i+1) chk=false;
    }
    if(chk) {
        cout << "ascending";
        return 0;
    }

    chk = true;
    for (int i = 0; i < 8; i++){
        if(note[i] != 8-i) chk=false;
    }
    if(chk) {
        cout << "descending";
        return 0;
    }

    cout << "mixed";
}