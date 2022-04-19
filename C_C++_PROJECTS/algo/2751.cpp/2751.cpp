#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> nums;

int main(void){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> N;
    int temp;
    for (int i = 0; i < N; i++) {
        cin >> temp;
        nums.push_back(temp);
    }
    
    sort(nums.begin(), nums.end());

    for (int i = 0; i < N; i++){
        cout << nums[i] << '\n';
    }    
}