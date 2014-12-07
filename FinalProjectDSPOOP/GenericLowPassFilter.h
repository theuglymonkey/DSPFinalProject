#ifndef GENERICL_FILTER_H_
#define GENERICL_FILTER_H_
#include "Arduino.h"

class GenericLowPassFilter
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
  GenericLowPassFilter(void);
  void Set2PoleCoefficents(float *inArray); // pass it an array of float that rep the coefficents
  void SetGainFactor(float gain);
  void InputData(float rawData);
  float OutputData();
  void PrintImpulseResponse(uint16_t sampCount, uint16_t passCount);


};

#endif
