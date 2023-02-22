#include <iostream>
#include "HourMeter.h"
#include <vector>
#include <numeric>
#include <random>
#include <array>
#define MAX_N 100'000'000
#define BOUND 1'000'000
#define SEED 6542
using namespace std;

vector<int> vector01;
long long sum;
int array01[MAX_N];
int* array02 = new int[MAX_N];
int* array03;
array<int, MAX_N> array04;
HourMeter hourmeter;

int main() {
  ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  random_device rd;
  mt19937 gen(SEED);
  uniform_int_distribution<int> dis(-BOUND, BOUND);
  int temp_input;
  array03 = (int*)malloc(sizeof(int) * MAX_N);
  for(int i=0; i<MAX_N; i++) {
    temp_input = dis(gen);
    vector01.push_back(BOUND);
    array01[i] = temp_input;
    array02[i] = temp_input;
    array03[i] = temp_input;
    array04[i] = temp_input;
  }
  cout << "gen end" << endl << endl;

  cout << endl << "vector - basic" <<endl;
  hourmeter.startMeasure();
  sum=0;
  for(int i=0; i<MAX_N; i++) {
    sum += vector01[i];
  }
  cout << sum << endl;
  hourmeter.endMeasure();

  cout << endl << "vector - accumulate" <<endl;
  hourmeter.startMeasure();
  cout << accumulate(vector01.begin(), vector01.end(), 0LL);
  hourmeter.endMeasure();
  
  cout << endl << "array1 - basic" <<endl;
  hourmeter.startMeasure();
  sum=0;
  for(int i=0; i<MAX_N; i++) {
    sum += array01[i];
  }
  cout << sum << endl;
  hourmeter.endMeasure();

  cout << endl << "array1 - pointer" <<endl;
  hourmeter.startMeasure();
  sum=0;
  for(int i=0; i<MAX_N; i++) {
    sum += *(array01 + i);
  }
  cout << sum << endl;
  hourmeter.endMeasure();

  cout << endl << "array2 - pointer" <<endl;
  hourmeter.startMeasure();
  sum=0;
  for(int i=0; i<MAX_N; i++) {
    sum += array02[i];
  }
  cout << sum << endl;
  hourmeter.endMeasure();

  cout << endl << "array3 - malloc" <<endl;
  hourmeter.startMeasure();
  sum=0;
  for(int i=0; i<MAX_N; i++) {
    sum += array03[i];
  }
  cout << sum << endl;
  hourmeter.endMeasure();

  cout << endl << "array4 - template" <<endl;
  hourmeter.startMeasure();
  sum=0;
  for(int i=0; i<MAX_N; i++) {
    sum += array04[i];
  }
  cout << sum << endl;
  hourmeter.endMeasure();

}



















HourMeter::HourMeter() :
	isMeasuring(false)
{
	printf("START HourMeter\n");
}

HourMeter::~HourMeter()
{
	printf("START ~HourMeter\n");
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