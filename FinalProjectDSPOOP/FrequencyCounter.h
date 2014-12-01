#ifndef FREQUENCY_COUNTER_
#define FREQUENCY_COUNTER_
#include "Arduino.h"

class FrequencyCounter
{
private:
  float previousFilteredData;
  bool previousVal;
  bool currentVal;
  bool zeroCrossed;
  int count;
  int zeroCount;
  long difference;
  float bpmValue;
  long stopTime, startTime;
  bool checkSignVal(int num);
public:
  FrequencyCounter(void);
  bool CalculateCrossing(float inputWave, bool printPeriod);
  void setPreviousVal(bool val);
  float getBPM();
  void StoreZeroCrossing(float num, int index);

};

#endif
