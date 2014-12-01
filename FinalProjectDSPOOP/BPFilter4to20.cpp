#include "BPFilter4to20.h"

BPFilter4to20::BPFilter4to20(void)
{
  for(int i =0; i < 5; i++)
  {
    xv[i]=0; // input to convolution is x variable
    yv[i]=0;
  }
}

void BPFilter4to20::InputData(float rawData)
{
// 4 to 17bpm (3 to 20 actual)
  xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4];
  xv[4] = (float)(rawData / 96.83753573);
  yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4];
  yv[4] =   (float)((xv[0] + xv[4]) - 2 * xv[2]
               + ( -0.7766480474 * yv[0]) + (  3.2767055922 * yv[1])
               + ( -5.2220325187 * yv[2]) + (  3.7219368150  * yv[3]));
}

float BPFilter4to20::OutputData()
{
  return yv[4];
}
