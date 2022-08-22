#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
typedef struct _sch{
    int start;
    int end;
} sch;
vector<sch> v;

bool comp(sch left, sch right){
    if(left.start == right.start) return left.end < right.end;
    return left.start < right.start;
}

int main() {
	int N, end, begin;
	cin >> N ;

	for (int i = 0; i < N; i++) {
		cin >> begin >> end;
		v.push_back({end, begin});
	}
	sort(v.begin(), v.end(), comp);
	
	int time = v[0].start;
	int count = 1;
	for (int i = 1 ;i < N; i++) {
		if (time <= v[i].end ){
			count++;
			time = v[i].start;
		}
	}

	cout << count;
}