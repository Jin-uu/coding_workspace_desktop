#include <bits/stdc++.h>

using namespace std;

#include <vector>
long long sum(std::vector<int> &a) {
	long long ans = 0;
    for (int i = 0; i < a.size(); i++) {
        ans += a[i];
    }
    
	return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);



    return 0;
}