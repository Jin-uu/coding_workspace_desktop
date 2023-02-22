#include <iostream>
#define MAX_N 100'000'000
#define BOUND 1'000'000

using namespace std;

int* arr;
long long ans;

int main() {
  ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  arr = (int*) malloc(sizeof(int) * MAX_N);
  for(int i=0; i<MAX_N; i++) cin >> arr[i];

  for(int i=0; i<MAX_N; i++) ans += arr[i];


  cout << ans;
}