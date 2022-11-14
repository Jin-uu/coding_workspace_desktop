#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_V 10'000
using namespace std;

typedef struct _edge {
    int from;
    int to;
    int weight;
} edge;

int vn, en, ans=0;
int uni[MAX_V+1];
vector<edge> v;

int get_par(int n) {
    if(uni[n] == n) return n;
    return uni[n] = get_par(uni[n]);
}

void merge_par(int a, int b) {
    a = get_par(a);
    b = get_par(b);
    uni[b] = a;
}

bool comp(edge left, edge right) {
    return left.weight < right.weight;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> vn >> en;
    int temp_f, temp_t, temp_w;
    for (int i = 0; i < en; i++) {
        cin >> temp_f >> temp_t >> temp_w;
        v.push_back({temp_f, temp_t, temp_w});
    }
    
    sort(v.begin(), v.end(), comp);

    for (int i = 1; i <= vn; i++) {
        uni[i] = i;
    }

    int v_cnt=0, idx=0, curr_f, curr_t, curr_w;
    while(v_cnt < vn-1){
        curr_f = v[idx].from; curr_t = v[idx].to; curr_w = v[idx].weight;
        idx++;
        if(get_par(curr_f) == get_par(curr_t)) continue;
        merge_par(curr_f, curr_t);
        ans += curr_w; v_cnt++;
    }

    cout << ans;
}