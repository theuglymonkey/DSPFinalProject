#ifndef ALARM_H_
#define ALARM_H_
#include "Arduino.h"

class Alarm
{
private:
  int32_t triggerLevel0;
  int32_t triggerLevel1;
  bool activated;

public:
    Alarm(void);
    void SetTriggerLevels(int32_t LowerBound,int32_t UpperBound );
    void Input(float inValue);
    bool Output();

};

#endif
