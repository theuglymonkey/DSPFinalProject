#ifndef GENERIC1_FILTER_H_
#define GENERIC1_FILTER_H_
#include "Arduino.h"

class Generic4PoleFilter
{
private:
  float xv[9]; // input to convolution is x variable
  float yv[9]; // output of convolution is y variable
  float preVal;
  float currentVal;
  float poleCoefficents[9];
  float gainFactor;
  //float 4poleCoefficents[8];
public:
  Generic4PoleFilter(void);
  void Set2PoleCoefficents(float *inArray); // pass it an array of float that rep the coefficents
  void SetGainFactor(float gain);
  void InputData(float rawData);
  float OutputData();
  float FirstDifference(float inData);
  void PrintImpulseResponse(uint16_t sampCount, uint16_t passCount);

};

#endif
