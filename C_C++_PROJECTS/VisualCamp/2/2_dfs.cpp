#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define MAX_N 100
#define MAX 100
using namespace std;
typedef struct _sch {
  int start;
  int len;
  int credit;
} sch;

int n, max_right=100;
int ans;
vector<int> ans_stk, stk;
vector<sch> v;

bool comp(sch left, sch right) {
  if(left.start == right.start) {
    if(left.len == right.len) return left.credit < right.credit;
    return left.len < right.len;
  }
  return left.start < right.start;
}

void dfs(int left, int total_credit) {
	int left_idx=-1;
  for(int i=0; i<n; i++) {
    if(left <= v[i].start) {left_idx = i; break;}
  }

	if(left > max_right || left_idx == -1){
		if(total_credit > ans){
			ans = total_credit;
			copy(stk.begin(), stk.end(), back_inserter(ans_stk));
		}
		return;
	}

	for(int i=left_idx; i<v.size(); i++) {
		stk.push_back(v[i].start);
		dfs(v[i].start+v[i].len, total_credit+v[i].credit);
		stk.pop_back();
	}
	return;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  cin >> n;

  int temp_start, temp_len, temp_credit;
  for(int i=0; i<n; i++) {
    cin >> temp_start >> temp_len >> temp_credit;
    v.push_back({temp_start, temp_len, temp_credit});
  }

  sort(v.begin(), v.end(), comp);
  max_right = v.back().start;

	dfs(0,0);
	cout << ans;

}

/*
5
0 4 5
3 4 20
6 6 3
8 5 35
10 4 12
*/