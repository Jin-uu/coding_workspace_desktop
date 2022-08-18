#include <iostream>
#include <vector>
#include <algorithm>
typedef struct _sch{
    int start;
    int end;
    int idx;
} sch;

using namespace std;

int n;
vector<sch> t,cpy;
int same[100'001];

bool comp_start(sch left, sch right){
    if(left.start == right.start) return left.end < right.end;
    return left.start < right.start;
}
bool comp_end(sch left, sch right){
    if(left.end == right.end) return left.start < right.start;
    return left.end < right.end;
}
bool f_start(sch left, sch right){
    return left.start < right.start;
}
bool f_end(sch left, sch right){
    return left.end < right.end;
}

int get_next(int left){
    sch target;
    target = {left, 0};
    int left_idx = lower_bound(t.begin(), t.end(), target, f_start) - t.begin();
    // cpy.clear();
    cpy.assign(t.begin()+left_idx, t.end());
    if(cpy.size() <= 0) return -1;
    sort(cpy.begin(), cpy.end(), comp_end);
    
    target = {0, left};
    int ans = lower_bound(cpy.begin(), cpy.end(), target, f_end) - cpy.begin();
    return t[cpy[ans].idx].end;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    t.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i].start >> t[i].end;
        if(t[i].start == t[i].end) same[t[i].start]++;
        t[i].idx = i;
    }
    sort(t.begin(), t.end(), comp_start);
    for (int i = 0; i < n; i++) {
        t[i].idx = i;
    }

    int curr = 0, next, cnt =0, flag_1, flag_2;
    flag_1 = get_next(curr); flag_2 = get_next(flag_1);
    if(flag_1 == flag_2 && same[flag_1] <= 1) {
        cnt--;
    }
    curr = 0;
    while((next = get_next(curr)) != -1){
        if(next == curr){
            cnt += same[next]; curr = next + 1;
            continue;
        }
        cnt++; curr = next; 
    }
    cout << cnt;
}