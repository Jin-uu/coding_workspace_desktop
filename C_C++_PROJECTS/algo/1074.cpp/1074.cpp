#include <iostream>
#include <cmath>

using namespace std;

int N, r, c;
int row[15];
int col[15];

int main(void) {
	cin >> N >> r >> c;

	for (int i = N-1; i >= 0; i--) {
		int div = pow(2, i);
		row[i] = (r / div) % 2;
		col[i] = (c / div) % 2;		
	}

	/*cout << "row[]: ";
	for (int i = 0; i < N; i++) {
		cout << row[i] << " ";
	}
	cout << endl;

	cout << "col[]: ";
	for (int i = 0; i < N; i++) {
		cout << col[i] << " ";
	}
	cout << endl;*/

	int cnt=0;
	for (int i = 0; i < N; i++) {
		int mul = pow(2, i*2);
		int mode = -1;
		if (row[i] && col[i]) mode = 4;
		if (row[i] && !col[i]) mode = 3;
		if (!row[i] && col[i]) mode = 2;
		if (!row[i] && !col[i]) mode = 1;
		
		cnt += mul * (mode - 1);
	}

	cout << cnt;
}