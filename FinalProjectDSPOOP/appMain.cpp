#include "appMain.h"
#include <avr/pgmspace.h>
#include "GenericFilter.h"
#include "Generic4PoleFilter.h"
#include "statistics.h"
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
    PROGMEM float filter1Coefficents[4] = {-0.8875204559, 3.6459232389, -5.6288902880, 3.8704751718};
    PROGMEM float filter1_2Coefficents[4] = {-0.8821677563, 3.6293674993, -5.6111685248, 3.8639259285};


    PROGMEM float filter2Coefficents[4] = {-0.7214500922, 3.0103189958, -4.8434854978, 3.5520478794};

    PROGMEM float filter2_2Coefficents[4] = {-0.6533308084, 2.8021605931, -4.6118955275, 3.4580896280};

    PROGMEM float filter3Coefficents[9] = {-0.2572128902, 1.2917875530, -3.5596180627, 6.6071273298,
                                           -8.9835506109,9.1610626304, -7.0184623574,3.6740462504 };

    PROGMEM float filter4Coefficents[4] = {-0.2781872758, 0.5438760383, -0.9387285737, 1.4813773641};
    SetupArduino();

    GenericFilter BP3to11;
    BP3to11.Set2PoleCoefficents(filter1Coefficents);
    BP3to11.SetGainFactor(405.5551166);

    GenericLowPassFilter BP3to11_2;
    BP3to11_2.Set2PoleCoefficents(filter1_2Coefficents);
    BP3to11_2.SetGainFactor(373366.8187);


    GenericFilter BP12to39;
    BP12to39.Set2PoleCoefficents(filter2Coefficents);
    BP12to39.SetGainFactor(58.86421797);

    GenericLowPassFilter BP12to39_2;
    BP12to39_2.Set2PoleCoefficents(filter2_2Coefficents);
    BP12to39_2.SetGainFactor(3215.359929);


    Generic4PoleFilter BP40to150;
    BP40to150.Set2PoleCoefficents(filter3Coefficents);
    BP40to150.SetGainFactor(43.44373910);

    //FrequencyCounter FC1;
    RunningStat rs1;
    RunningStat rs2;
    RunningStat rs3;

    Alarm alarmLow;
    Alarm alarmNormal;
    Alarm alarmHigh;
    alarmLow.SetTriggerLevels(8000,100000);
    alarmNormal.SetTriggerLevels(450,4500);
    alarmHigh.SetTriggerLevels(200,550);

    int preDa = 0;
    int curDa;
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

         //inputAvData = (preDa + inputAvData)/2;
         //preDa = inputAvData;

        //  Serial.println(inputAvData);
         //BP3to11.InputData(inputAvData);
         BP3to11_2.InputData(inputAvData);
         //BP3to11_2.InputData(BP3to11.OutputData());

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
              rs1.Clear();
           }
           else if(count > 200)
           {
             //rs1.Push(BP3to11_2.OutputData());
             rs2.Push(BP12to39_2.OutputData());
             rs3.Push(BP40to150.OutputData());
           }

         }
         else
         {
           count++;
           //rs1.Push(BP3to11_2.OutputData());
           rs2.Push(BP12to39_2.OutputData());
           rs3.Push(BP40to150.OutputData());

           //alarmLow.Input(rs1.Variance());
           alarmNormal.Input(rs2.Variance());
           alarmHigh.Input(rs3.Variance());
           if(count > 855) // every min
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

             rs1.Clear();
             rs2.Clear();
             rs3.Clear();
             count = 256;
           }
             //Serial.println("clear");


            //Serial.print(rs1.Variance());
            //Serial.print(BP3to11_2.OutputData());
            //Serial.print(" ");

            Serial.print(rs2.Variance());
            //Serial.print(BP12to39_2.OutputData());
            Serial.print(" ");
            Serial.print(rs3.Variance());
            //Serial.print(BP40to150.OutputData());
            Serial.println(" ");


         }

         Flag_for_sample = 0;
      }
    }
}
