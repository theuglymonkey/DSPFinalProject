#include "appMain.h"
#include "HighPass50Bpm.h"
#include "BPFilter4to20.h"
#include <MsTimer2.h>
#include "FrequencyCounter.h"
volatile static int Flag_for_sample=0;
volatile static int countMax = 0;
void Sample_Flag()
{
  Flag_for_sample = 1;
}

AppMain::AppMain(void)
{
  count = 0;
}

void AppMain::SetupArduino(void)
{
  Serial.begin(9600);
  analogReference(DEFAULT);  // for 5.0 volt power supply reference
  delay(500);

  // Make two reads from A/D to get it running and eliminate first few bad values

  MsTimer2::set(100, Sample_Flag); // set sample period in miliseconds
  MsTimer2::start();
}

void AppMain::AppMainLoop(void)
{
    volatile static int analogValue =0;
    volatile static float sum=0;
    volatile static int inputAvData = 0;

    SetupArduino();
    BPFilter4to20 BP4to20;
    HighPass50Bpm Hp50;
    FrequencyCounter FC1;
    FrequencyCounter FC2;
    for(;;)
    {
      if (Flag_for_sample>0)
      {
        sum=0;

         for (int i=0; i < 100; i++)
         {
           // read the analog input into a variable:
           analogValue = analogRead(0);
           sum=sum+(float)analogValue;
         }
         inputAvData=100.0*(sum/100.0);
         BP4to20.InputData(inputAvData);
         //Hp50.InputData(inputAvData);
         //Serial.println(Hp50.OutputData());

         if(count < 250)
         {
           count++;
           Serial.println(BP4to20.OutputData());
           if(count == 250)
           {
             Serial.println("start");
           }
         }
         else
         {

              //Serial.println(Lp50.OutputData());
              FC1.CalculateCrossing(BP4to20.OutputData(), true);
              //FC2.CalculateCrossing(Hp50.OutputData(), true);
              //Serial.println(Lp50.OutputData());
         }

         Flag_for_sample = 0;
      }
    }
}
