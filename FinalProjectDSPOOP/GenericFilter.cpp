#include "GenericFilter.h"
int count1 = 0;

GenericFilter::GenericFilter(void)
{
  for(int i =0; i < 5; i++)
  {
    xv[i]=0; // input to convolution is x variable
    yv[i]=0;
  }
}

void GenericFilter::Set2PoleCoefficents(float *inArray)
{
  for(int i = 0; i < 4; i++)
  {
    poleCoefficents[i] = inArray[i];
  }
}
void GenericFilter::SetGainFactor(float gain)
{
  gainFactor = gain;
}

void GenericFilter::InputData(float rawData)
{
// 21 to 40bpm (19 to 45 actual)
  xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4];
  xv[4] = (float)(rawData / gainFactor);
  yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4];
  yv[4] =   (float)((xv[0] + xv[4]) - 2 * xv[2]
               + ( poleCoefficents[0] * yv[0]) + (  poleCoefficents[1] * yv[1])
               + ( poleCoefficents[2] * yv[2]) + (  poleCoefficents[3]  * yv[3]));
}

float GenericFilter::OutputData()
{
  return yv[4];
}

float GenericFilter::FirstDifference(float inData)
{
  float returnVal;
  if(count1 < 1)
  {
    preVal = inData;
    count1++;
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

void GenericFilter::PrintImpulseResponse(uint16_t sampCount, uint16_t passCount) // set the filter coefficents before using this function
{
    if( sampCount  == 3)
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
