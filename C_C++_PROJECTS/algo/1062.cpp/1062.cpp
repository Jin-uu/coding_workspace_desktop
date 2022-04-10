#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int N, K;
bool isStudied[27];
vector<string> words;
int MAX = 0;

int c_to_i(char alpha) {
	return alpha - 'a' + 1;
}

int get_readable_words_num() {
	int cnt = 0;
	bool check;
	for (int i = 0; i < N; i++) {
		check = true;
		for (int j = 0; j < words[i].size(); j++) {
			if (!isStudied[c_to_i(words[i].at(j))]) {
				check = false;
				break;
			}
		}
		if (check) cnt++;
	}

	return cnt;
}

void dfs(int n, int last_word_index) {
	if (n == K) {
		MAX = max(MAX, get_readable_words_num());
		return;
	}

	for (int i = last_word_index+1; i <= 26; i++) {
		if (isStudied[i]) continue;
		isStudied[i] = true;
		dfs(n + 1, i);
		isStudied[i] = false;
	}
}


int main(void) {
	cin >> N >> K;

	isStudied[c_to_i('a')] = true;
	isStudied[c_to_i('c')] = true;
	isStudied[c_to_i('i')] = true;
	isStudied[c_to_i('n')] = true;
	isStudied[c_to_i('t')] = true;

	for (int i = 0; i < N; i++) {
		char temp[16];
		cin >> temp;
		words.push_back(temp);
	}

	dfs(5, 1);
	cout << MAX;

	return 0;
}