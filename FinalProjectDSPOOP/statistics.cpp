#include "statistics.h"

statistics::statistics() {
	running_sum = 0.0;
	running_count = 0;
	first = true;
	}

void statistics::add(float filter_value)
{
	filterValue = filter_value;
	running_sum = running_sum + filterValue;
	running_count = running_count + 1;
}

float statistics::get_std_dev() {
	float variance  = get_variance();
	return sqrt(variance);
}

float statistics::get_mean(void) {
	return (float)(running_sum / (float)running_count);
}

float statistics::get_variance() {
	add(filterValue);
	float variance;
	float filter_mean = get_mean();
	float summation = (running_sum*running_sum) - ((running_sum*running_sum)/(float)running_count);
	if(first){
		variance  =  (summation)/(float)(running_count-1);
		first = false;
	}
	variance = summation;
	return variance;
}
