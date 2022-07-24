#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#define MAX_N 300'000
typedef long long ll;

using namespace std;

ll n;
ll Answer;
vector<ll> P, V;
vector<pair<ll,ll>> S;

bool cpr(pair<ll,ll> left, pair<ll,ll> right){
    if(left.first == right.first){
        return left.second < right.second;
    }
    return left.first < right.first;
}

int main(int argc, char** argv){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	ll T, test_case, temp_input;

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++) {
        cin >> n;
        P.clear(); V.clear(); S.clear(); Answer =0;

        for (ll i = 0; i < n; i++) {
            cin >> temp_input;
            P.push_back(temp_input);
        }
        for (ll i = 0; i < n; i++) {
            cin >> temp_input;
            V.push_back(temp_input); S.push_back({temp_input, P[i]});
        }

        sort(S.begin(), S.end(), cpr);
    
        for (ll i = 0; i < n; i++) {

            Answer += abs(S[i].second - P[i]);
        }
		cout << "Case #" << test_case+1 << '\n';
		cout << Answer << '\n';
	}

	return 0;
}