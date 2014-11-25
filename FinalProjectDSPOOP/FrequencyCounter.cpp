#include "FrequencyCounter.h"

FrequencyCounter::FrequencyCounter(void)
{
  count = 0;
  zeroCount = 0;
  zeroCrossed = false;
}

void FrequencyCounter::CalculateCrossing(float inputWave, bool printPeriod)
{
  if(count < 1 )
  {
    previousVal = checkSignVal((int)inputWave);
    count++;
  }
  else
  {
    currentVal = checkSignVal((int)inputWave);
    if(previousVal != currentVal)
    {
      zeroCrossed = true;
      zeroCount++;

      if(zeroCount == 6) // final crossin
      {
        if(inputWave < 5 && inputWave > -5)
        {
          stopTime = micros();
          //Serial.println("stop");
          if(printPeriod == true)
          {
            difference = stopTime - startTime;
            //Serial.println(getBPM());
            Serial.println(difference/2);
          }
          zeroCount = 0;
        }
      }
      else if(zeroCount == 1) // first crossing
      {
        if(inputWave < 5 && inputWave > -5)
        {
          startTime = micros();
        }
      }
    }
    else
    {
      zeroCrossed = false;
    }
    previousVal = currentVal;
  }
}

bool FrequencyCounter::checkSignVal(int num)
{
  int abNum = abs(num);
  return (abNum != num);
}

float FrequencyCounter::getBPM()
{
  bpmValue = float(60/(difference*(.000001)));
  return bpmValue;
}
