#ifndef HIGH_PASS_50_BPM_
#define HIGH_PASS_50_BPM_
#include "Arduino.h"

class HighPass50Bpm
{
private:
  float xv[4]; // input to convolution is x variable
  float yv[4]; // output of convolution is y variable

public:
  HighPass50Bpm(void);
  void InputData(float rawData);
  float OutputData();

};

#endif
