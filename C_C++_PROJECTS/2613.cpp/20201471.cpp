#include <iostream>
using namespace std;

#define MAX 300

int n, m;
int B[MAX] = {};

void printBGroups(int k){
    int left = 0;
    int right = 0;
    int curr_sum=0;
    for(int i=0; i<m; i++){
        if(n-right <= m-i){
            for(int j=0; j<n-right; j++){
                cout << "1 ";
            }
            return;
        }
        while(curr_sum + B[right] <= k){
            if(right >= n-1) {
                right++;
                break;
            }
            curr_sum += B[right];
            right++;
        }
        cout << right - left << " ";
        left = right;
        curr_sum = 0;
    }
}

bool isPos(int k) {
    int cnt = 0;
    int curr_idx =-1;
    int curr_sum =0;
    int curr_group_cnt =0;

    while(curr_group_cnt < m) {
        curr_sum = 0;
        while(curr_sum + B[curr_idx+1] <= k) {
            curr_sum += B[++curr_idx];
            if(curr_idx == n-1){
                return true;
            }
        }
        curr_group_cnt++;
    }
    if(curr_idx <= n) return false;
}

int main() {
    int max_B = -1;

    cin >> n;
    cin >> m;
    for(int i=0; i<n; i++){
        cin >> B[i];
        if(max_B < B[i]) max_B = B[i];
    }

    int left = max_B;
    int right = 100 * MAX;
    int mid = -1;
    int ans = -1;

    while(left <= right){
        mid = (left + right) / 2;
        if(isPos(mid)){
            ans = mid;
            right = mid-1;
        }
        else{
            left = mid+1;
        }
    }

    cout << ans << endl;
    printBGroups(ans);
    return 0;
}
