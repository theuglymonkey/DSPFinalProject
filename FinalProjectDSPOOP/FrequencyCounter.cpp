#include "FrequencyCounter.h"

FrequencyCounter::FrequencyCounter(void)
{
  count = 0;
  zeroCount = 0;
  zeroCrossed = false;
}

bool FrequencyCounter::CalculateCrossing(float inputWave, bool printPeriod)
{
  if(count < 1 )
  {
    if(inputWave > 4 || inputWave < -4)
    {
      previousVal = checkSignVal((int)inputWave);
      count++;
    }
  }
  else
  {
    if(inputWave > 4 || inputWave < -4)
    {
      currentVal = checkSignVal((int)inputWave);

      if(previousVal != currentVal)
      {
          zeroCrossed = true;
          //Serial.print(inputWave);
          //Serial.print(" ");
          zeroCount++;

        if(zeroCount == 3) // final crossing
        {
            stopTime = micros();
            //Serial.println("stop");
            if(printPeriod == true)
            {
              difference = stopTime - startTime;
              Serial.println(getBPM());
              //Serial.println(difference);
            }
          zeroCount = 0;
        }
        else if(zeroCount == 1) // first crossing
        {
            startTime = micros();
        }

      }
      else
      {
        zeroCrossed = false;
      }
      previousVal = currentVal;
    }
  }
  return zeroCrossed;
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

void FrequencyCounter::StoreZeroCrossing(float num, int index)
{

}
