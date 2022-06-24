#include <bits/stdc++.h>

using namespace std;

string a,b;
int ans[10001];
int ans_len;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> a >> b;
    while(a[0] == '0'){
        a.erase(0,1);
    }
    while(b[0] == '0'){
        b.erase(0,1);
    }


    ans_len = max(a.size(), b.size())+1;

    int l,r,curr, check=0;
    for (int i = 0; i < ans_len; i++) {
        if(a.size() < i+1) l = 0;
        else l = a[a.size()-i-1]-'0';
        if(b.size() < i+1) r = 0;
        else r = b[b.size()-i-1]-'0';
        curr = l+r;
        if(check) curr++;
        if(curr >= 10) {check = 1; curr %= 10;}
        else check = 0;
        
        ans[ans_len-i-1] = curr;
    }

    for (int i = 0; i < ans_len; i++) {
        if(i==0 && ans[i] == 0) continue;
        cout << ans[i];
    }
    
    


    return 0;
}