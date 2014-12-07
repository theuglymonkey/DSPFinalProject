#include "Generic4PoleFilter.h"
int count2 = 0;

Generic4PoleFilter::Generic4PoleFilter(void)
{
  for(int i =0; i < 9; i++)
  {
    xv[i]=0; // input to convolution is x variable
    yv[i]=0;
  }
}

void Generic4PoleFilter::Set2PoleCoefficents(float *inArray)
{
  for(int i = 0; i < 9; i++)
  {
    poleCoefficents[i] = inArray[i];
  }
}
void Generic4PoleFilter::SetGainFactor(float gain)
{
  gainFactor = gain;
}

void Generic4PoleFilter::InputData(float rawData)
{
  xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4]; xv[4] = xv[5]; xv[5] = xv[6]; xv[6] = xv[7]; xv[7] = xv[8];
  xv[8] = (float)(rawData / gainFactor);
  yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4]; yv[4] = yv[5]; yv[5] = yv[6]; yv[6] = yv[7]; yv[7] = yv[8];
  yv[8] =   (float)((xv[0] + xv[8]) - 4 * (xv[2] + xv[6]) + 6 * xv[4]
               + ( poleCoefficents[0] * yv[0]) + (  poleCoefficents[1]* yv[1])
               + ( poleCoefficents[2] * yv[2]) + (  poleCoefficents[3]* yv[3])
               + ( poleCoefficents[4] * yv[4]) + (  poleCoefficents[5] * yv[5])
               + ( poleCoefficents[6] * yv[6]) + (  poleCoefficents[7] * yv[7]));

}

float Generic4PoleFilter::OutputData()
{
  return yv[4];
}

float Generic4PoleFilter::FirstDifference(float inData)
{
  float returnVal;
  if(count2 < 1)
  {
    preVal = inData;
    count2++;
    returnVal = preVal;
  }
  else
  {
    currentVal = inData;
    returnVal = ((currentVal - preVal)/.1);
    preVal = currentVal;
  }
  return returnVal;
}

void Generic4PoleFilter::PrintImpulseResponse(uint16_t sampCount, uint16_t passCount) // set the filter coefficents before using this function
{
  if(sampCount == 3)
  {
    if(passCount == 2)
    {
      InputData(OutputData());
    }
    InputData(1);

  }
  else
  {
    if(passCount == 2)
    {
      InputData(OutputData());
    }
      InputData(0);
  }
  Serial.println(OutputData());
}
