#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_N 100
#define MAX 100
using namespace std;

typedef struct _sch {
  int start;
  int len;
  int credit;
} sch;
typedef struct _return_pair {
  int ret;
  vector<int> stk;
} return_pair;

int n, max_right=100;
vector<sch> v;
vector<return_pair> dp_tbl;

bool comp(sch left, sch right) {
  if(left.start == right.start) {
    if(left.len == right.len) return left.credit < right.credit;
    return left.len < right.len;
  }
  return left.start < right.start;
}

void init_dp() {
  dp_tbl.resize(MAX+1);
  for(int i=0; i<=MAX; i++) {
    dp_tbl[i].ret = -1;
    dp_tbl[i].stk.clear();
  }
}

return_pair dp(int left) {
  if(left > max_right) return {0};

  return_pair& return_ret =  dp_tbl[left];
  if(return_ret.ret != -1) return return_ret;

  int left_idx=-1;
  for(int i=0; i<n; i++) {
    if(left <= v[i].start) {left_idx = i; break;}
  }
  if(left_idx == -1) return return_ret = {0};

  int curr_sum, max_idx;
  return_pair curr_pair, max_ret;
  for(int i=left_idx; i<n; i++) {
    curr_pair = dp(v[i].start + v[i].len);
    curr_sum = v[i].credit + curr_pair.ret;
    if(return_ret.ret < curr_sum) {
      return_ret.ret = curr_sum;
      max_ret = curr_pair;
      max_idx = i;
    }
  }
  copy(max_ret.stk.begin(), max_ret.stk.end(), back_inserter(return_ret.stk));
  return_ret.stk.push_back(max_idx);
  return return_ret;
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
  init_dp();
  max_right = v.back().start;

  return_pair ans_pair = dp(0);
  for(int i=ans_pair.stk.size()-1; i>=0; i--) {
    cout << v[ans_pair.stk[i]].start << ' ' << v[ans_pair.stk[i]].len << '\n';
  }
  cout << ans_pair.ret << endl;
}