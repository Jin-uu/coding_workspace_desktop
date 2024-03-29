#include "HourMeter.h"

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

	printf("수행시간: %lf\n", result_sec);
}

double HourMeter::getLatestDuration()
{
	return result_sec.count();
}