#include "iGEM-Madrid-OLM.h"


    msgReceiver::msgReceiver(HardwareSerial* serial_)
    {
		serial = serial_;
    }


    int msgReceiver::receiver()
    {
        jsonBuffer_ = StaticJsonBuffer<2000>(); 
        long W8Time = millis();
			
        while ((millis() - W8Time) < 200)
        {
            while (serial->available())
            {
                W8Time = millis();
                char c = (char)serial->read();
  
                buf += c;


            
                if (c == '\n')
                {
                    break;
                }
            }
        }
        root  = jsonBuffer_.parseObject(buf);
        if (!root.success())
		{
			buf = "";
            return -1;
		}
        // Serial.println(buf);
		buf = "";
        return 0;
    
    }
    
    int msgReceiver::understand(motorHandler motorHandler_)
    {       
	
		//motor command handling
        String buff = root["motors"];
		if(buff != "") {
		   if (root["motors"].size()>motorHandler_.motorNumber)
		   {
			   Serial.println("WARNING: You have entered commands for more motors than initialized ones.\n\nOnly the commands for the initialized motors will run:\n");
		   }
			

            for (int i=0; i < motorHandler_.motorNumber; i++)
            {
                buff = String("Motor " + String(i+1) + ":");
                
				//Steps detected	
				int steps = root["motors"][i]["steps"];
                if (steps != 0)
                        {
                             buff += String(" Steps = " + String(steps));
							 motorHandler_.motor[i]->move(steps);
                        }
						
				//Maximun speed detected
				float MaxSpeed = root["motors"][i]["maxSpeed"];
				if (MaxSpeed > 0 && MaxSpeed <= 100)
				{
					buff += String(" Maximun speed = " + String(MaxSpeed));
					motorHandler_.motor[i]->setMaxSpeed(map(MaxSpeed,0,100,10,900));
				}

				//Speed detected
                float speed = root["motors"][i]["speed"];
                if (speed != 0)          
                        {
							 motorHandler_.motor[i]->setMaxSpeed(900);
							 motorHandler_.motor[i]->setSpeed(map(speed, -100, 100, -900,900));
                             buff += String(" Speed = " + String(speed));
                        } else motorHandler_.motor[i]->setSpeed(0);
						
				//Acceleration detected
				float acceleration = root["motors"][i]["acc"];
				if (acceleration > 0)
				{
					buff += String(" Acceleration = " + String(acceleration));
					motorHandler_.motor[i]->setAcceleration(acceleration);
				} 	
			Serial.println(buff);
			Serial.println();
			buff = "";
										
            }
        }
        
		buff = "";
		root["potentiostat"].printTo(buff);
		if(buff != "") {
			root["potentiostat"]["command"].printTo(buff);
			if (buff.indexOf("runTest")!=-1)
			{
				root["potentiostat"]["test"].printTo(buff);
				if (buff.indexOf("cyclic")!=-1)
				{					
					String msg = root["potentiostat"];
					Serial2.println(msg);
					receiveCyclic();
				}
			} else {
				String msg = root["potentiostat"];
				Serial2.println(msg);
			}
		}

        return 0;
    }
	
	int msgReceiver::receiveCyclic()
	{
		
        buf = "";


		while(Serial2.available() < 2); //Wait for data to start arriving

			while (Serial2.available()) //repeat until stop receiving data
			{
				while (buf.indexOf('}') == -1) //stop the read ar each line
				{

					char c = (char)Serial2.read();
	  
					if( c != -1 && c!='\n') buf += c; //ignore end of line and "-1" which mean no values readed				
				
				}

				//ACT WITH THIS DATA
				jsonBuffer_ = StaticJsonBuffer<2000>(); 
				root = jsonBuffer_.parseObject(buf);
				root["v"].printTo(Serial);
				buf = "";
			}

		
			return 0;
		
	}
    
    motorHandler::motorHandler ()
     {}
 
	void motorHandler::runMotors ()
	{
		//Run for each motor
		for (int i = 0; i < motorNumber; i++)
		{
			//check if the motor needs to step more
		
				//Is adjusted runSpeed completely? If not, try with run
				if (motor[i]->speed() != 0 && motor[i]->speed() < 901)
				{
					if (motor[i]->distanceToGo() != 0)
					{
						isRunning[i] = true;
						motor[i]->runSpeedToPosition();
					} else {
						if (isRunning[i] == true)
						{
							Serial.println(String("Motor " + String(i+1) + " has stopped"));
							isRunning[i] = false;
						}
					}

				}
			
		}
	}
	 
    
    motorHandler::motorHandler (int pina1, int pina2, int pina3, int pina4)
    {
        motor = new AccelStepper* [1];
        motorNumber = 1;
		isRunning = new bool [motorNumber];
        
        motor[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        
    }
    

    motorHandler::motorHandler (int pina1, int pina2, int pina3, int pina4,int pinb1, int pinb2, int pinb3, int pinb4)
    {
        motor = new AccelStepper* [2];
        motorNumber = 2;
		isRunning = new bool [motorNumber];
        
        motor[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motor[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
    }

    motorHandler::motorHandler (int pina1, int pina2, int pina3, int pina4,
								 int pinb1, int pinb2, int pinb3, int pinb4,
								 int pinc1, int pinc2, int pinc3, int pinc4)
    {
        motor = new AccelStepper* [3];
        motorNumber = 3;
		isRunning = new bool [motorNumber];
        
        motor[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motor[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
        motor[2] = new AccelStepper(AccelStepper::FULL4WIRE, pinc1,pinc2,pinc3,pinc4);
    }

   motorHandler::motorHandler (int pina1, int pina2, int pina3, int pina4,
								 int pinb1, int pinb2, int pinb3, int pinb4,
								 int pinc1, int pinc2, int pinc3, int pinc4,
								 int pind1, int pind2, int pind3, int pind4)
    {
        motor = new AccelStepper* [4];
       motorNumber = 4;
	   isRunning = new bool [motorNumber];
        
        motor[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motor[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
        motor[2] = new AccelStepper(AccelStepper::FULL4WIRE, pinc1,pinc2,pinc3,pinc4);
        motor[3] = new AccelStepper(AccelStepper::FULL4WIRE, pind1,pind2,pind3,pind4);
    }

    motorHandler::motorHandler (int pina1, int pina2, int pina3, int pina4,
								 int pinb1, int pinb2, int pinb3, int pinb4,
								 int pinc1, int pinc2, int pinc3, int pinc4,
								 int pind1, int pind2, int pind3, int pind4,
								 int pine1, int pine2, int pine3, int pine4)
    {
        motor = new AccelStepper* [5];
        motorNumber = 5;
		isRunning = new bool [motorNumber];
        
        motor[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motor[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
        motor[2] = new AccelStepper(AccelStepper::FULL4WIRE, pinc1,pinc2,pinc3,pinc4);
        motor[3] = new AccelStepper(AccelStepper::FULL4WIRE, pind1,pind2,pind3,pind4);
        motor[4] = new AccelStepper(AccelStepper::FULL4WIRE, pine1,pine2,pine3,pine4);

    }

    motorHandler::motorHandler ( int pina1, int pina2, int pina3, int pina4,
								 int pinb1, int pinb2, int pinb3, int pinb4,
								 int pinc1, int pinc2, int pinc3, int pinc4,
								 int pind1, int pind2, int pind3, int pind4,
								 int pine1, int pine2, int pine3, int pine4,
								 int pinf1, int pinf2, int pinf3, int pinf4)
    {
        motor = new AccelStepper* [6];
        motorNumber = 6;
		isRunning = new bool [motorNumber];
        
        motor[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motor[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
        motor[2] = new AccelStepper(AccelStepper::FULL4WIRE, pinc1,pinc2,pinc3,pinc4);
        motor[3] = new AccelStepper(AccelStepper::FULL4WIRE, pind1,pind2,pind3,pind4);
        motor[4] = new AccelStepper(AccelStepper::FULL4WIRE, pine1,pine2,pine3,pine4);
        motor[5] = new AccelStepper(AccelStepper::FULL4WIRE, pinf1,pinf2,pinf3,pinf4);
    
    }

    motorHandler::motorHandler (int pina1, int pina2, int pina3, int pina4,
								int pinb1, int pinb2, int pinb3, int pinb4,
								int pinc1, int pinc2, int pinc3, int pinc4,
								int pind1, int pind2, int pind3, int pind4,
								int pine1, int pine2, int pine3, int pine4,
								int pinf1, int pinf2, int pinf3, int pinf4,
								int ping1, int ping2, int ping3, int ping4)
    {
        motor = new AccelStepper* [7];
        motorNumber = 7;
		isRunning = new bool [motorNumber];
        
        motor[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motor[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
        motor[2] = new AccelStepper(AccelStepper::FULL4WIRE, pinc1,pinc2,pinc3,pinc4);
        motor[3] = new AccelStepper(AccelStepper::FULL4WIRE, pind1,pind2,pind3,pind4);
        motor[4] = new AccelStepper(AccelStepper::FULL4WIRE, pine1,pine2,pine3,pine4);
        motor[5] = new AccelStepper(AccelStepper::FULL4WIRE, pinf1,pinf2,pinf3,pinf4);
        motor[6] = new AccelStepper(AccelStepper::FULL4WIRE, ping1,ping2,ping3,ping4);

    }

    motorHandler::motorHandler ( int pina1, int pina2, int pina3, int pina4,
								 int pinb1, int pinb2, int pinb3, int pinb4,
								 int pinc1, int pinc2, int pinc3, int pinc4,
								 int pind1, int pind2, int pind3, int pind4,
								 int pine1, int pine2, int pine3, int pine4,
								 int pinf1, int pinf2, int pinf3, int pinf4,
								 int ping1, int ping2, int ping3, int ping4,
								 int pinh1, int pinh2, int pinh3, int pinh4)
	{
        motor = new AccelStepper* [8];
        motorNumber = 8;
		isRunning = new bool [motorNumber];
        
        motor[0] = new AccelStepper(AccelStepper::FULL4WIRE, pina1,pina2,pina3,pina4);
        motor[1] = new AccelStepper(AccelStepper::FULL4WIRE, pinb1,pinb2,pinb3,pinb4);
        motor[2] = new AccelStepper(AccelStepper::FULL4WIRE, pinc1,pinc2,pinc3,pinc4);
        motor[3] = new AccelStepper(AccelStepper::FULL4WIRE, pind1,pind2,pind3,pind4);
        motor[4] = new AccelStepper(AccelStepper::FULL4WIRE, pine1,pine2,pine3,pine4);
        motor[5] = new AccelStepper(AccelStepper::FULL4WIRE, pinf1,pinf2,pinf3,pinf4);
        motor[6] = new AccelStepper(AccelStepper::FULL4WIRE, ping1,ping2,ping3,ping4);
        motor[7] = new AccelStepper(AccelStepper::FULL4WIRE, pinh1,pinh2,pinh3,pinh4);
    }
	
    





