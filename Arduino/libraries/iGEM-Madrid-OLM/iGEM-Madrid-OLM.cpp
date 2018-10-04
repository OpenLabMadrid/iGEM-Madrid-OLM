#include "iGEM-Madrid-OLM.h"


    msgReceiver::msgReceiver()
    {
    }


    int msgReceiver::receiver()
    {
        jsonBuffer_ = StaticJsonBuffer<200>(); 
        long W8Time = millis();
        
        while ((millis() - W8Time) < 100)
        {
            while (Serial.available())
            {
                W8Time = millis();
                char c = (char)Serial.read();
  
                buf += c;
            
                if (c == '\n')
                {
                    break;
                }
            }
        }
        
        root  = jsonBuffer_.parseObject(buf);
        if (!root.success())
            return ERR_PARS;
        Serial.println(buf);
        buf = "";
        return 0;
    
    }
    
    int msgReceiver::understand(motorHandler motorHandler_)
    {       
        root["motors"];
        
       if (root["motors"].size()>motorHandler_.motorNumber)
       {
           Serial.println("WARNING: You have entered commands for more motors than initialized ones.\n\nOnly the commands for the initialized motors will run:\n");
       }
        
        if(root.success())
        {
            for (int i=0; i < motorHandler_.motorNumber; i++)
            {
                buf = String("Motor " + String(i+1) + ":");
                             
                int speed = root["motors"][i]["speed"];
                if (speed > 0)
                        {
                             buf += String(" Speed = " + String(speed));
                        }
                int steps = root["motors"][i]["steps"];
                if (steps > 0)
                        {
                             buf += String(" Steps = " + String(steps));
                        }

                
                Serial.println(buf);
                Serial.println();
                buf = "";
            }
        }
        

        return 0;
    }
    
    motorHandler::motorHandler ()
     {}
    
    motorHandler::motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4)
    {
        motors = new AccelStepper* [1];
        motorNumber = 1;
        
        motors[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        
    }
    

    motorHandler::motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4, int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4)
    {
        motors = new AccelStepper* [2];
        motorNumber = 2;
        
        motors[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motors[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
    }

    motorHandler::motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                                     int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4,
                                     int stepsPerRevc, int pinc1, int pinc2, int pinc3, int pinc4)
    {
        motors = new AccelStepper* [3];
        motorNumber = 3;
        
        motors[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motors[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
        motors[2] = new AccelStepper(AccelStepper::FULL4WIRE, pinc1,pinc2,pinc3,pinc4);
    }

   motorHandler::motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                                     int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4,
                                     int stepsPerRevc, int pinc1, int pinc2, int pinc3, int pinc4,
                                     int stepsPerRevd, int pind1, int pind2, int pind3, int pind4)
    {
        motors = new AccelStepper* [4];
       motorNumber = 4;
        
        motors[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motors[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
        motors[2] = new AccelStepper(AccelStepper::FULL4WIRE, pinc1,pinc2,pinc3,pinc4);
        motors[3] = new AccelStepper(AccelStepper::FULL4WIRE, pind1,pind2,pind3,pind4);
    }

    motorHandler::motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                                     int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4,
                                     int stepsPerRevc, int pinc1, int pinc2, int pinc3, int pinc4,
                                     int stepsPerRevd, int pind1, int pind2, int pind3, int pind4,
                                     int stepsPerReve, int pine1, int pine2, int pine3, int pine4)
    {
        motors = new AccelStepper* [5];
        motorNumber = 5;
        
        motors[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motors[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
        motors[2] = new AccelStepper(AccelStepper::FULL4WIRE, pinc1,pinc2,pinc3,pinc4);
        motors[3] = new AccelStepper(AccelStepper::FULL4WIRE, pind1,pind2,pind3,pind4);
        motors[4] = new AccelStepper(AccelStepper::FULL4WIRE, pine1,pine2,pine3,pine4);

    }

    motorHandler::motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                                     int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4,
                                     int stepsPerRevc, int pinc1, int pinc2, int pinc3, int pinc4,
                                     int stepsPerRevd, int pind1, int pind2, int pind3, int pind4,
                                     int stepsPerReve, int pine1, int pine2, int pine3, int pine4,
                                     int stepsPerRevf, int pinf1, int pinf2, int pinf3, int pinf4)
    {
        motors = new AccelStepper* [6];
        motorNumber = 6;
        
        motors[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motors[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
        motors[2] = new AccelStepper(AccelStepper::FULL4WIRE, pinc1,pinc2,pinc3,pinc4);
        motors[3] = new AccelStepper(AccelStepper::FULL4WIRE, pind1,pind2,pind3,pind4);
        motors[4] = new AccelStepper(AccelStepper::FULL4WIRE, pine1,pine2,pine3,pine4);
        motors[5] = new AccelStepper(AccelStepper::FULL4WIRE, pinf1,pinf2,pinf3,pinf4);
    
    }

    motorHandler::motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                                     int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4,
                                     int stepsPerRevc, int pinc1, int pinc2, int pinc3, int pinc4,
                                     int stepsPerRevd, int pind1, int pind2, int pind3, int pind4,
                                     int stepsPerReve, int pine1, int pine2, int pine3, int pine4,
                                     int stepsPerRevf, int pinf1, int pinf2, int pinf3, int pinf4,
                                     int stepsPerRevg, int ping1, int ping2, int ping3, int ping4)
    {
        motors = new AccelStepper* [7];
        motorNumber = 7;
        
        motors[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motors[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
        motors[2] = new AccelStepper(AccelStepper::FULL4WIRE, pinc1,pinc2,pinc3,pinc4);
        motors[3] = new AccelStepper(AccelStepper::FULL4WIRE, pind1,pind2,pind3,pind4);
        motors[4] = new AccelStepper(AccelStepper::FULL4WIRE, pine1,pine2,pine3,pine4);
        motors[5] = new AccelStepper(AccelStepper::FULL4WIRE, pinf1,pinf2,pinf3,pinf4);
        motors[6] = new AccelStepper(AccelStepper::FULL4WIRE, ping1,ping2,ping3,ping4);

    }

    motorHandler::motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                                     int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4,
                                     int stepsPerRevc, int pinc1, int pinc2, int pinc3, int pinc4,
                                     int stepsPerRevd, int pind1, int pind2, int pind3, int pind4,
                                     int stepsPerReve, int pine1, int pine2, int pine3, int pine4,
                                     int stepsPerRevf, int pinf1, int pinf2, int pinf3, int pinf4,
                                     int stepsPerRevg, int ping1, int ping2, int ping3, int ping4,
                                     int stepsPerRevh, int pinh1, int pinh2, int pinh3, int pinh4)
    {
        motors = new AccelStepper* [8];
        motorNumber = 8;
        
        motors[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motors[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
        motors[2] = new AccelStepper(AccelStepper::FULL4WIRE, pinc1,pinc2,pinc3,pinc4);
        motors[3] = new AccelStepper(AccelStepper::FULL4WIRE, pind1,pind2,pind3,pind4);
        motors[4] = new AccelStepper(AccelStepper::FULL4WIRE, pine1,pine2,pine3,pine4);
        motors[5] = new AccelStepper(AccelStepper::FULL4WIRE, pinf1,pinf2,pinf3,pinf4);
        motors[6] = new AccelStepper(AccelStepper::FULL4WIRE, ping1,ping2,ping3,ping4);
        motors[7] = new AccelStepper(AccelStepper::FULL4WIRE, pinh1,pinh2,pinh3,pinh4);
    }
    
    motorHandler::adjustMotors (int motor, int speed_, int steps_)
    {
        int speed = 0;
        speed = map(speed_, 0, 100, 10,900);
        
    }

    motorHandler::adjustMotors (int motor, int steps_)
    {
        
    }
