#include "LowPass50Bpm.h"

LowPass50Bpm::LowPass50Bpm(void)
{
  for(int i =0; i < 4; i++)
  {
    xv[i]=0; // input to convolution is x variable
    yv[i]=0;
  }
}

void LowPass50Bpm::InputData(float rawData)
{
/*This is a low pass filter with an fc = 0.833333333
*This filter is accurate between 0 and 50bpm give or take 1.5bpm */
  xv[0] = xv[1]; xv[1] = xv[2];
  xv[2] = (float)(rawData / 13.69533901);
  yv[0] = yv[1]; yv[1] = yv[2];
  yv[2] =   (float)((xv[0] + xv[2]) - 2 * xv[1]
  + ( -0.4875486213 * yv[0]) + (  1.1954784509 * yv[1]));
}

float LowPass50Bpm::OutputData()
{
  return yv[2];
}