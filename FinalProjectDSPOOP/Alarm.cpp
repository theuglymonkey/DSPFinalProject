#include "Alarm.h"

Alarm::Alarm()
{
  activated = false;
}

void Alarm::SetTriggerLevels(int32_t LowerBound,int32_t UpperBound )
{
  triggerLevel0 = LowerBound;
  triggerLevel1 = UpperBound;
}

void Alarm::Input(float inValue)
{
  if(inValue > triggerLevel0 && inValue < triggerLevel1)
  {
    activated = true;
  }
  else
  {
    activated = false;
  }
}

bool Alarm::Output()
{
  return activated;
}
