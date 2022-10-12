#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>
#define INF INT_MAX
using namespace std;

int n, ans=INF, ans_l=-1, ans_r=-1;
vector<int> v;


int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n;
    int temp;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        v.push_back(temp);
    }

    int left = 0, right = n-1, curr_diff;
    while(left < right) {
        curr_diff = v[left] + v[right]; 
        // cout << left << " " << right << " " << curr_diff<< endl;
        if(ans > abs(curr_diff)){
            ans = abs(curr_diff);
            ans_l = left;
            ans_r = right;
        }
        if(curr_diff == 0) break;
        if(curr_diff < 0) left++;
        if(curr_diff > 0) right--;
    }

    // cout << ans_l << " " << ans_r;
    cout << v[ans_l] << " " << v[ans_r];
}