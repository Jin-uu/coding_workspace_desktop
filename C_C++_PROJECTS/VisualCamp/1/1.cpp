#include <iostream>
#include <vector>
#include <cstring>
#define MAX_N 1'000
#define MAX 1'000'000

using namespace std;

int n;
vector<int> v;
bool isNPrime[MAX+1];

void eratos() {
	memset(isNPrime, false, sizeof(isNPrime));
	for(int i=2; i<=MAX; i++) {
		if(isNPrime[i]) continue;
		for(int j=i+i; j<=MAX; j+=i) isNPrime[j] = true;
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;

	v.resize(n);
	for(int i=0; i<n; i++) cin >> v[i];

	eratos();
	
	for(int i=0; i<v.size(); i++) {
		if(isNPrime[v[i]]) cout << "false\n";
		if(!isNPrime[v[i]]) cout << "true\n";
	}
}

/*
5
10 4 12     
8 5 35
6 6 3
3 4 20
0 4 5
=================
5
8 6 12     
8 5 35
3 4 3
3 4 20
0 4 5
-----------------
0 4 5
3 4 3
3 4 20
8 5 35
8 6 12
=================
*/