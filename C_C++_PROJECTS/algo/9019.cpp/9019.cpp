#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>

#define MAX 10000

using namespace std;

int T, A, B;
bool v[MAX + 1];

void init(void) {
	for (int i = 0; i <= MAX; i++) {
		v[i] = false;
	}
}

void solve(int a, int b) {
	queue<pair<string, int>> q;		// <D,a>
	q.push({ "", a });
	v[A] = true;

	while (!q.empty()) {
		string curr_s = q.front().first;
		int curr_n = q.front().second;
		q.pop();

		if (curr_n == B) {
			cout << curr_s << '\n';
		}

		int next;
		//D
		next = (curr_n * 2) % MAX;
		if (!v[next]) {
			v[next] = true;
			q.push({ curr_s + "D" , next });
		}
		//S
		if (curr_n == 0) next = 9999;
		else next = curr_n - 1;
		if (!v[next]) {
			v[next] = true;
			q.push({ curr_s + "S" , next });
		}
		//L
		next = (curr_n%1000) * 10 + curr_n/1000;
		if (!v[next]) {
			v[next] = true;
			q.push({ curr_s + "L" , next });
		}
		//R
		next = (curr_n / 10) + (curr_n % 10) * 1000;
		if (!v[next]) {
			v[next] = true;
			q.push({ curr_s + "R" , next });
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> A >> B;
		init();
		solve(A, B);
	}
}