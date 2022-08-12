#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#define INF INT_MAX

using namespace std;

int n,m, dgt=0;
vector<int> brk, tgt;

bool isPos(int n){
    for (int i = 0; i < brk.size(); i++) {
        if(n == brk[i]) return false;
    }
    return true;
}

int lower_n(){
    int flag = tgt[0], l_n=0, fnal=0;
    vector<int> ret;
    ret.resize(dgt);

    while(flag > 0){
        if(isPos(flag)) break;
        flag--;
    }
    ret[0] = flag;
    
    for (int i = 1; i < tgt.size(); i++) {
        flag = 9;
        if(ret[i-1] == tgt[i-1]) flag = tgt[i];
        while(flag >= 0){
            if(isPos(flag)) break;
            flag--;
        }
        if(flag == -1) return INF;
        ret[i] = flag;
    }
        
    for (int i = 0; i < ret.size(); i++) {
        l_n *= 10;
        l_n += ret[i];
    }
    fnal += ret.size();
    for (int i = 0; i < ret.size(); i++) {
        if(ret[i] != 0) break;
        fnal--;
    }
    if(l_n == 0) fnal = 1;
    fnal += n - l_n;
    // cout << "lower : " << fnal << ",";
    // for (int i = 0; i < ret.size(); i++) {
    //     cout << ret[i];
    // }
    // cout << endl;
    
    return fnal;
}

int upper_n(){
    int flag = tgt[0], l_n=0, fnal=0;
    vector<int> ret;
    ret.resize(dgt);

    while(flag < 10){
        if(isPos(flag)) break;
        flag++;
    }
    if(flag == 10) return INF;
    ret[0] = flag;
    
    for (int i = 1; i < tgt.size(); i++) {
        flag = 0;
        if(ret[i-1] == tgt[i-1]) flag = tgt[i];
        while(flag < 10){
            if(isPos(flag)) break;
            flag++;
        }
        if(flag == 10) return INF;
        ret[i] = flag;
    }
        
    for (int i = 0; i < ret.size(); i++) {
        l_n *= 10;
        l_n += ret[i];
    }
    fnal += ret.size();
    for (int i = 0; i < ret.size(); i++) {
        if(ret[i] != 0) break;
        fnal--;
    }
    fnal += l_n -n;
    // cout << "upper : " << fnal << ", ";
    // for (int i = 0; i < ret.size(); i++) {
    //     cout << ret[i];
    // }
    // cout << endl;
    return fnal;
}

int main(void){
    cin >> n >> m;
    brk.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> brk[i];
    }

    int cpy = n;
    while(cpy != 0) {
        tgt.push_back(cpy % 10);
        cpy /= 10;
        dgt++;
    }
    reverse(tgt.begin(), tgt.end());
    cout << min({lower_n(), upper_n(), abs(n-100)});
}