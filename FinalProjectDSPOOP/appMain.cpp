#include "appMain.h"
#include <avr/pgmspace.h>
#include "GenericFilter.h"
#include "Generic4PoleFilter.h"
#include "RunningStat.h"
#include <MsTimer2.h>
#include "FrequencyCounter.h"
#include "GenericLowPassFilter.h"
#include "GenericHighPassFilter.h"
#include "Alarm.h"
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
  pinMode(2, INPUT_PULLUP);

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
  //  PROGMEM float filter1Coefficents[4] = {-0.8875204559, 3.6459232389, -5.6288902880, 3.8704751718};
  //  PROGMEM float filter1_2Coefficents[4] = {-0.8821677563, 3.6293674993, -5.6111685248, 3.8639259285};

    PROGMEM float filter2Coefficents[4] = {-0.7214500922, 3.0103189958, -4.8434854978, 3.5520478794};

    PROGMEM float filter2_2Coefficents[4] = {-0.6533308084, 2.8021605931, -4.6118955275, 3.4580896280};

    PROGMEM float filter3Coefficents[9] = {-0.2572128902, 1.2917875530, -3.5596180627, 6.6071273298,
                                           -8.9835506109,9.1610626304, -7.0184623574,3.6740462504 };

    SetupArduino();

    //GenericFilter BP3to11;
    //BP3to11.Set2PoleCoefficents(filter1Coefficents);
    //BP3to11.SetGainFactor(405.5551166);

    //GenericLowPassFilter BP3to11_2;
    //BP3to11_2.Set2PoleCoefficents(filter1_2Coefficents);
    //BP3to11_2.SetGainFactor(373366.8187);


    GenericFilter BP12to39;
    BP12to39.Set2PoleCoefficents(filter2Coefficents);
    BP12to39.SetGainFactor(58.86421797);

    GenericLowPassFilter BP12to39_2;
    BP12to39_2.Set2PoleCoefficents(filter2_2Coefficents);
    BP12to39_2.SetGainFactor(3215.359929);


    Generic4PoleFilter BP40to150;
    BP40to150.Set2PoleCoefficents(filter3Coefficents);
    BP40to150.SetGainFactor(43.44373910);

    RunningStat rs2;
    RunningStat rs3;

    Alarm alarmNormal;
    Alarm alarmHigh;

    alarmNormal.SetTriggerLevels(450,4500);
    alarmHigh.SetTriggerLevels(190,1000);

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

         BP12to39.InputData(inputAvData);
         BP12to39_2.InputData(BP12to39.OutputData());

         BP40to150.InputData(inputAvData);

        /*wait 250 samples to stabalize filter*/
         if(count < 256)
         {
           count++;
           /*
          if(count == 3)
          {
            //BP3to11.InputData(1);
            //BP3to11_2.InputData(BP3to11.OutputData());

            BP12to39.InputData(1);
            BP12to39_2.InputData(BP12to39.OutputData());

          }
          else
          {
            //BP3to11.InputData(0);
            //BP3to11_2.InputData(BP3to11.OutputData());
            BP12to39.InputData(0);
            BP12to39_2.InputData(BP12to39.OutputData());

          }
          Serial.println(BP12to39_2.OutputData());
*/

           if(count == 256)
           {
              Serial.println("start");
           }
           else if(count > 200)
           {
             rs2.Push(BP12to39_2.OutputData());
             rs3.Push(BP40to150.OutputData());
           }

         }
         else
         {
           count++;
           rs2.Push(BP12to39_2.OutputData());
           rs3.Push(BP40to150.OutputData());

           alarmNormal.Input(rs2.Variance());
           alarmHigh.Input(rs3.Variance());
           if(count > 855) // every min 855
           {
             if(digitalRead(2) != 1)
             {
               if(alarmNormal.Output() == true)
               {
                 Serial.println("Normal");
               }
               else if(alarmHigh.Output() == true)
               {
                 Serial.println("High");
               }
               else
               {
                 Serial.println("Low");
               }
             }
             else
             {
               Serial.println("Error Sensor Disconnected");
             }

             rs2.Clear();
             rs3.Clear();
             count = 256;
           }

            Serial.print(rs2.Variance());
            //Serial.print(BP12to39_2.OutputData());
            Serial.print(" ");
            Serial.print(rs3.Variance());
            //Serial.print(B P40to150.OutputData());
            Serial.println(" ");


         }

         Flag_for_sample = 0;
      }
    }
}
