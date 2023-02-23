#include <iostream>
#include <thread>
#include "HourMeter.h"
#include <vector>
#include <numeric>
#include <random>
#include <array>
#define MAX_N 100'000'000
#define BOUND 1'000'000
#define THREAD_NUM 500
// const int UNIT = MAX_N / THREAD_NUM;
#define SEED 1234
using namespace std;

vector<int> v;
vector<long long> partial_sums;
vector<thread> workers;
HourMeter hourmeter;

void worker(vector<int>::iterator start, vector<int>::iterator end,
            long long* result) {
  long long sum = 0;
  for (auto itr = start; itr < end; ++itr) {
    sum += *itr;
  }
  *result = sum;
}

void start_culc(int thread_num) {
  cout << "[thread " << thread_num << "]\n";
  hourmeter.startMeasure();
  partial_sums.clear();
  partial_sums.resize(thread_num);
  workers.clear();

  int unit = MAX_N / thread_num;
  for(int i=0; i<thread_num; i++) {
    workers.push_back(thread(worker, v.begin() + i * unit, v.begin() + (i + 1) * unit, &partial_sums[i]));
  }

  for(int i=0; i<thread_num; i++) {
    workers[i].join();
  }

  long long total =0;
  for(int i=0; i<thread_num; i++) {
    total += partial_sums[i];
  }

  cout << "total : " << total << endl;
  hourmeter.endMeasure();
}

int main() {
  ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  random_device rd;
  mt19937 gen(SEED);
  uniform_int_distribution<int> dis(-BOUND, BOUND);

  int temp_input;

  for(int i=0; i<MAX_N; i++) {
    temp_input = dis(gen);
    v.push_back(BOUND);
  }
  cout << "gen end\n\n";

  int n;
  while(1) {
    cin >> n;
    start_culc(n);
  }

  start_culc(1000);
  // start_culc(1);
  // start_culc(2);
  // start_culc(3);
  // start_culc(4);
  // start_culc(5);
  // start_culc(6);
  // start_culc(7);
  // start_culc(8);
  // start_culc(9);
  for(int i=10; i<=1000; i+=10) {
    start_culc(i);
  }

}



















HourMeter::HourMeter() :
	isMeasuring(false)
{
	printf("START HourMeter\n");
}

HourMeter::~HourMeter()
{
	// printf("START ~HourMeter\n");
}

void HourMeter::startMeasure()
{
	if (isMeasuring == true) {
		printf("FAIL startMeasure; already measuring\n");
		throw std::runtime_error("startMeasure");
	}

	isMeasuring = true;
	begin = std::chrono::system_clock::now();
}

void HourMeter::endMeasure()
{
	if (isMeasuring == false) {
		printf("FAIL endMeasure; not measuring\n");
		throw std::runtime_error("endMeasure");
	}

	end = std::chrono::system_clock::now();
	result_sec = end - begin;
	isMeasuring = false;

	printf("수행시간: %lf\n====================\n", result_sec);
}

double HourMeter::getLatestDuration()
{
	return result_sec.count();
}