#ifndef APP_MAIN_H
#define APP_MAIN_H
#include "Arduino.h"

class AppMain
{
private:
    int count;
    void SetupArduino(void);
public:
    AppMain(void);
    void AppMainLoop(void);

};

#endif
