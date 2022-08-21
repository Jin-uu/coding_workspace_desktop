#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef struct _node{
    char left;
    char right;
} node;

int n;
vector<node> v;
void pre_order(char curr){
    if(curr == '.') return;
    cout << curr;
    pre_order(v[(curr) - 'A'].left);
    pre_order(v[(curr) - 'A'].right);
}
void in_order(char curr){
    if(curr == '.') return;
    in_order(v[(curr) - 'A'].left);
    cout << curr;
    in_order(v[(curr) - 'A'].right);
}
void post_order(char curr){
    if(curr == '.') return;
    post_order(v[(curr) - 'A'].left);
    post_order(v[(curr) - 'A'].right);
    cout << curr;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n;
    v.resize(n);
    char t_x, t_l, t_r;
    for (int i = 0; i < n; i++) {
        cin >> t_x >> t_l >> t_r;
        v[t_x - 'A'] = {t_l, t_r};
    }
    pre_order('A'); cout << '\n';
    in_order('A'); cout << '\n';
    post_order('A'); cout << '\n';
}