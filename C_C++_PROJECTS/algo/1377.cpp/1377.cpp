#define DEBUG
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

vector<pair<int,int>> A;
vector<pair<int, int>> C;
int N;
set<int> elems;


int compare(const pair<int,int> a,const pair<int,int> b){
	if (a.first < b.first) return 1;
	else if (a.first > b.first) return -1;
	return 0;
}

int main(void) {
	cin >> N;

	for (int i = 1; i <= N; i++) {
		int temp_input;
		cin >> temp_input;
		A.push_back(make_pair(temp_input, i));
		C.push_back(make_pair(temp_input, i));
	}

	/*cout << "A : ";
	for (int i = 0; i <N; i++) {
		cout << A[i].first<< "[" << A[i].second << "]" << " ";
	}
	cout << endl;*/

	stable_sort(C.begin(), C.end());


	//cout << "sorted : ";
	//for (int i = 0; i < N; i++) {
	//	cout << C[i].first << "[" << C[i].second << "]" << " ";
	//}
	//cout << endl;
	
	int max_move = 0;
	for (int i = 0; i < N; i++) {
		max_move = max(max_move, C[i].second - i);
	}

	cout << max_move;

	//bool changed = false;
	//for (int i = 1; i <= N + 1; i++) {
	//	changed = false;
	//	for (int j = 1; j <= N - i; j++) {
	//		if (A[j] > A[j + 1]) {
	//			changed = true;
	//			swap(A[j], A[j + 1]);
	//		}
	//	}
	//	if (changed == false) {
	//		cout << endl << "ans : " << i << '\n';
	//		break;
	//	}
	//}


}