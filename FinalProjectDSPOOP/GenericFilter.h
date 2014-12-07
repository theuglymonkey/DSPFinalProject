#ifndef GENERIC_FILTER_H_
#define GENERIC_FILTER_H_
#include "Arduino.h"

class GenericFilter
{
private:
  float xv[5]; // input to convolution is x variable
  float yv[5]; // output of convolution is y variable
  float preVal;
  float currentVal;
  float poleCoefficents[4];
  float gainFactor;
  //float 4poleCoefficents[8];
public:
  GenericFilter(void);
  void Set2PoleCoefficents(float *inArray); // pass it an array of float that rep the coefficents
  void SetGainFactor(float gain);
  void InputData(float rawData);
  float OutputData();
  float FirstDifference(float inData);
  void PrintImpulseResponse(uint16_t sampCount, uint16_t passCount);


};

#endif
