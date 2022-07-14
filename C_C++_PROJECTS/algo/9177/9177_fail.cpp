#include <iostream>
#include <cstring>

using namespace std;

int n;
string s1, s2, tgt;


bool solve(int left, int right, int idx){
    // cout << left << "," << right << "," << idx << endl;
    if(left==s1.length() && right==s2.length()) {
        // cout << "finished!\n";
        return true;
    }
    if(left < s1.length() && s1[left] == tgt[idx]){
        // cout << "left >> ";
        if(solve(left+1, right, idx+1)) return true;
    }
    if(right < s2.length() && s2[right] == tgt[idx]){
        // cout << "right >> ";
        if(solve(left, right+1, idx+1)) return true;
    }
    return false;
}

int main(void){
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> s1 >> s2 >> tgt;
        // cout << s1.length() << s2.length() << tgt.length() << endl;
        if(solve(0, 0, 0)) cout << "Data set " << i+1 <<": yes" << endl;
        else cout << "Data set " << i+1 <<": no" << endl;
    }
}