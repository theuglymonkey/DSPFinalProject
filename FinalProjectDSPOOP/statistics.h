#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "Arduino.h"

class statistics  {
	private:
	int get_size();
	float running_sum;
	int running_count;
	bool first;
	float filterValue;

	public:
	statistics();
	void add(float filter_value);
	float get_std_dev();
	float get_mean();
	float get_variance();

};

#endif;
