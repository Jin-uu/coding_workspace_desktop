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

typedef struct _return_pair {
  int ret;
  vector<int> stk;
} return_pair;

int n, max_right=100;
vector<sch> v;
vector<int> ans;
int dp_tbl[MAX+1];


bool comp(sch left, sch right) {
  if(left.start == right.start) {
    if(left.len == right.len) return left.credit < right.credit;
    return left.len < right.len;
  }
  return left.start < right.start;
}

int dp(int left) {
  if(left > max_right) return 0;

  int& ret = dp_tbl[left];
  if(ret != -1) return ret;
  cout << left << endl;

  int left_idx=-1;
  for(int i=0; i<n; i++) {
    if(left <= v[i].start) {
      left_idx = i; break;
    }
  }
  if(left_idx == -1) return ret = 0;

  int now, max_idx;
  for(int i=left_idx; i<n; i++) {
    now = v[i].credit + dp(v[i].start + v[i].len);
    if(ret < v[i].credit + dp(v[i].start + v[i].len)) {
      ret = now;
      max_idx = i;
    }
  }
  ans.push_back(max_idx);

  return ret;
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
  memset(dp_tbl, -1, sizeof(dp_tbl));
  max_right = v.back().start;

  cout << dp(0) << endl;
}

/*
5
0 4 5
3 4 20
6 6 3
8 5 35
10 4 12
*/