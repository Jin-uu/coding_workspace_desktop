#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 50
#define MAX_M 10000
using namespace std;

int n,m;
int pointer[MAX_N+1], chk[MAX_M+1];
vector<int> crn,box;

bool isFin(){
    for (int i = 0; i < n; i++) if(pointer[i] >= 0) return false;
    return true;
}

bool isPos(){
    for (int i = 0; i < m; i++) if(!chk[i]) return false;
    return true;    
}

int solve(){
    for (int i = 0; i < n; i++){
        pointer[i] = upper_bound(box.begin(), box.end(), crn[i]) - box.begin();
    }
    int ans=0;
    while(!isFin()){
        ans++;
        for (int i = 0; i < n; i++){
            pointer[i]--; if(pointer[i] < 0) continue;
            while(chk[pointer[i]]){
                pointer[i]--; if(pointer[i] < 0) continue;
            }
            if(pointer[i] < 0) continue;
            chk[pointer[i]] = true;
        }
    }
    if(!isPos()) return -1;
    return ans-1;
}

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n; crn.resize(n);
    for (int i = 0; i < n; i++) cin >> crn[i];
    cin >> m; box.resize(m);
    for (int i = 0; i < m; i++) cin >> box[i];

    sort(crn.begin(), crn.end()); sort(box.begin(), box.end());

    cout << solve();
}