// SCPC 6회 예선
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 200'000

using namespace std;

int Answer;
int n, k;
vector<int> vec_a, vec_b;

int main(int argc, char** argv) {
	int T, test_case;

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++) {
		Answer = 0; vec_a.clear(); vec_b.clear();

        cin >> n >> k;
        int temp_input;
        for (int  i = 0; i < n; i++) {
            cin >> temp_input;
            vec_a.push_back(temp_input);
        }
        for (int  i = 0; i < n; i++) {
            cin >> temp_input;
            vec_b.push_back(temp_input);
        }
        
        sort(vec_a.begin(), vec_a.end());
        sort(vec_b.begin(), vec_b.end());
        
        for (int i = 0; i < k; i++) {
            Answer = max(Answer, vec_a[i]+vec_b[k-i-1]);
        }       


		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}