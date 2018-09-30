#include "iGEM_Motor_Control.h"
#include <ctype.h>

#define MAX_MOTORS 8


String buff;
int bytesReceived = 0;
unsigned long StepTime;

motorControl* motor [MAX_MOTORS];


void setup() {
  Serial.begin(9600);

  StepTime = micros();

  motor[0] = new motorControl (8,9,10,11);
  motor[1] = new motorControl (15,16,17,18);
  motor[2] = new motorControl (0,0,0,0);
  motor[3] = new motorControl (0,0,0,0);
  motor[4] = new motorControl (0,0,0,0);
  motor[5] = new motorControl (0,0,0,0);
  motor[6] = new motorControl (0,0,0,0);
  motor[7] = new motorControl (0,0,0,0);
 
}

void loop() {

  while (Serial.available()) 
  {
    if (bytesReceived < 100)
      buff += (char)Serial.read();
    else
      Serial.read();
    bytesReceived++;
    delay(5);
  }

  if (bytesReceived)
  {
    Serial.print(buff);
    Serial.println(" ");
    int i=1;

      /////////////////////SERIAL PARSING///////////////////
      parsing();
      /////////////////////////////////////////////////////////////////////////
    
    bytesReceived = 0; //Reset the counter for receive new commands 
    buff = "";
  }

  if (micros() - StepTime > 800)
  {
    RunMotors ();
    StepTime = micros();
  }
  
  // put your main code here, to run repeatedly:

}
void RunMotors ()
{
  for (int i = 0 ; i < MAX_MOTORS; i++)
  {
    if(motor[i]->steps > 0)
    {
      if(motor[i]->CW == true)
        {
          motor[i]->oneStepCW();
        } else {
          motor[i]->oneStepACW();
        }

       motor[i]->steps--;
    }
  }
}
void parsing ()
{
  int motorNumber;
  String Speed;
  String loops;
  bool CW = true;
  
  int i = 0; //for walking through the string buffer
  char c = '\0';

  buff.toUpperCase();
  
  while (buff.charAt(i) != '\n')
  {
    while (buff.charAt(i) != ' ' && buff.charAt(i) != '\n')
    {
      //Skipping numbers
      
      while (isdigit(buff.charAt(i)))
      {
        i++;
      }
      c = buff.charAt(i);

      switch (c)
      {
        case 'M':
              i++;
              motorNumber = buff.charAt(i) - '0';
              i++;
          break;
        case 'L':
              i++;
              while (isdigit(buff.charAt(i)))
              {
                loops += buff.charAt(i);
                i++;
              }
          break;
        case 'S':
              i++;
              if (!isdigit(buff.charAt(i)))
              {
                if(buff.charAt(i) == '-')
                CW = false;
                i++;
              }
      
              while (isdigit(buff.charAt(i)))
               {
                 Speed += buff.charAt(i);
                 i++;
               }
          break;
      }
    }
    
    if (motor[motorNumber-1]->motorPin1 > 0)
    {
      if (Speed.length() > 0)
      {
        motor[motorNumber-1]->Speed = Speed.toInt();
      }
      if (loops.length() > 0)
        motor[motorNumber-1]->steps = (unsigned long int) ((unsigned long int) loops.toInt() * (unsigned long int) motor[motorNumber-1]->stepsPerRev);
      motor[motorNumber-1]->CW = CW;

       Speed = "";
       loops = "";
       CW = true;

      Serial.println("Motor number: " + String(motorNumber) + " ; Speed: " + String(motor[motorNumber-1]->Speed) + " ; Steps: " + String(motor[motorNumber-1]->steps));
    } else {
      Serial.println("ERR0R: NO MOTOR WAS FOUND");
    }
    if (buff.charAt(i) == ' ')
      i++;
  }
}

/*while (isdigit(buff.charAt(i)))
      {
        motorNumber += buff.charAt(i);
        i++;
      }
      Serial.print(String("Motor number = " + motorNumber));

      i++;
      if (!isdigit(buff.charAt(i)))
      {
        if(buff.charAt(i) == '-')
        CW = false;
        i++;
      }
      
      while (isdigit(buff.charAt(i)))
      {
        Speed += buff.charAt(i);
        i++;
      }
      Serial.print(String(" ; Speed = " + Speed));

      i++;

      while (isdigit(buff.charAt(i)))
      {
        loops += buff.charAt(i);
        i++;
      }
      Serial.println(String(" ; Loop number = " + loops));
      */

