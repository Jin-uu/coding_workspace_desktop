#include <iostream>
#include <cstring>
#include <algorithm>
#define MAX 500
using namespace std;

int n,m;
string dp_tbl[MAX+1][MAX+1];

string add_s(string left, string right){
    int sum = 0;
    string result;
    while (!left.empty() || !right.empty() || sum) {
        if (!left.empty()){
            sum += left.back() - '0'; left.pop_back();
        }
        if (!right.empty()) {
            sum += right.back() - '0'; right.pop_back();
        }
        result.push_back((sum % 10) + '0');
        sum /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

string solve(int n, int r){
    if(r == 0 || r == n) return "1";
    if(r == 1) return to_string(n);

    string &ret = dp_tbl[n][r];
    if(ret != "") return ret;

    return ret = add_s(solve(n-1, r), solve(n-1, r-1));
}

int main(void){
    cin >> n >> m;
    cout << solve(n,m);
}