#ifndef BP_FILTER_4_TO_20_H_
#define BP_FILTER_4_TO_20_H_
#include "Arduino.h"

class BPFilter4to20
{
private:
  float xv[5]; // input to convolution is x variable
  float yv[5]; // output of convolution is y variable

public:
  BPFilter4to20(void);
  void InputData(float rawData);
  float OutputData();

};

#endif
