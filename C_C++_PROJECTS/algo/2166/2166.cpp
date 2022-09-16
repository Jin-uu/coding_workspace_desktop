#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef struct _node{
    int x;
    int y;
} node;

int n;
vector<node> v;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n;
    int temp_x, temp_y;
    for (int i = 0; i < n; i++) {
        cin >> temp_x >> temp_y;
        v.push_back({temp_x, temp_y});
    }

    int left, right;
    long long ans=0;
    for (int i = 0; i < n; i++) {
        left = i; right = ((i+1 < n) ? i+1 : 0);
        ans += (long long)v[left].x * (long long)v[right].y; 
        ans -= (long long)v[right].x * (long long)v[left].y;
    }

    printf("%.1f\n", (double)abs(ans) * 0.5);
}