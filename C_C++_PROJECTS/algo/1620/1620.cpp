#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define MAX_N 100'000
using namespace std;

int n, m;
vector<string> dict;
vector<pair<string,int>> sorted_dict;

bool comp(pair<string,int> left, pair<string, int> right){ return left.first < right.first; }

int solve(string tgt){
    pair<string,int> target = {tgt, -1};
    return sorted_dict[lower_bound(sorted_dict.begin(), sorted_dict.end(), target, comp) - sorted_dict.begin()].second;
}

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m; dict.resize(n+1); sorted_dict.resize(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> dict[i]; sorted_dict[i].first = dict[i]; sorted_dict[i].second = i;
    }
    sort(sorted_dict.begin(), sorted_dict.end(), comp);    

    string temp;
    for (int i = 0; i < m; i++) {
        cin >> temp;
        if(isdigit(temp[0])){
            cout << dict[stoi(temp)] << '\n'; continue;
        }
        cout << solve(temp) << '\n';
    }
}