#ifndef LOW_PASS_50_BPM_
#define LOW_PASS_50_BPM_
#include "Arduino.h"

class LowPass50Bpm
{
private:
  float xv[5]; // input to convolution is x variable
  float yv[5]; // output of convolution is y variable

public:
  LowPass50Bpm(void);
  void InputData(float rawData);
  float OutputData();

};

#endif
