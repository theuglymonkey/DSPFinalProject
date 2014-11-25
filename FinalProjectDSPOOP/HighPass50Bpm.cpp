#include "HighPass50Bpm.h"

HighPass50Bpm::HighPass50Bpm(void)
{
  for(int i =0; i < 4; i++)
  {
    xv[i]=0; // input to convolution is x variable
    yv[i]=0;
  }
}

void HighPass50Bpm::InputData(float rawData)
{
  /*This is a low pass filter with an fc = 0.833333333
  *This filter is accurate between 0 and 50bpm give or take 1.5bpm */
  xv[0] = xv[1]; xv[1] = xv[2];
  xv[2] = (float)(rawData / 12.99294895);
  yv[0] = yv[1]; yv[1] = yv[2];
  yv[2] =   (float)((xv[0] + xv[2]) - 2 * xv[1]
  + ( -0.6121867657 * yv[0]) + (  1.4664061035 * yv[1]));
}

float HighPass50Bpm::OutputData()
{
  return yv[2];
}
