#ifndef GENERICH_FILTER_H_
#define GENERICH_FILTER_H_
#include "Arduino.h"

class GenericHighPassFilter
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
  GenericHighPassFilter(void);
  void Set2PoleCoefficents(float *inArray); // pass it an array of float that rep the coefficents
  void SetGainFactor(float gain);
  void InputData(float rawData);
  float OutputData();
  void PrintImpulseResponse(uint16_t sampCount, uint16_t passCount);


};

#endif
