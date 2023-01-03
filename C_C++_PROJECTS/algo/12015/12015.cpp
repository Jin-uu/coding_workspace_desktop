#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n,curr;
vector<int> nums;
vector<int> dp_tbl;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n;
    nums.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    dp_tbl.push_back(nums[0]);
    for (int i = 1; i < n; i++) {
        curr = nums[i];
        if(dp_tbl.back() < curr){
            dp_tbl.push_back(curr);
            continue;
        }
        dp_tbl[lower_bound(dp_tbl.begin(), dp_tbl.end(), curr) - dp_tbl.begin()] = curr;
    }

    cout << dp_tbl.size();    
}