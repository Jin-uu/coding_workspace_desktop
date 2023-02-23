#include <iostream>
#include <thread>
#include <vector>
#define MAX_N 100'000'000
#define BOUND 1'000'000
#define THREAD_NUM 50
#define UNIT 2'000'000    // MAX_N / THREAD_NUM
using namespace std;

vector<int> v;
vector<long long> partial_sums;
vector<thread> workers;

void worker(vector<int>::iterator start, vector<int>::iterator end, long long* result) {
  long long sum = 0;
  for (auto itr = start; itr < end; ++itr) sum += *itr;

  *result = sum;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  v.resize(MAX_N);
  for(int i=0; i<MAX_N; i++) {
    cin >> v[i];
  }

  partial_sums.resize(THREAD_NUM);
  for(int i=0; i<THREAD_NUM; i++) {
    workers.push_back(thread(worker, v.begin() + i * UNIT, v.begin() + (i + 1) * UNIT, &partial_sums[i]));
  }

  for(int i=0; i<THREAD_NUM; i++) workers[i].join();

  long long total =0;
  for(int i=0; i<THREAD_NUM; i++) total += partial_sums[i];


  cout << total;
}