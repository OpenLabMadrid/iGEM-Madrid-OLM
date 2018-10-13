#ifndef IGEM_MADRID_OLM
#define IGEM_MADRID_OLM

#include <Arduino.h>
#include <ArduinoJson.h>
#include <AccelStepper.h>





class motorHandler
{

    public:
    
    AccelStepper** motor;
	
    int motorNumber;
	bool* isRunning;
    
    motorHandler ();
	void runMotors();
	
	
	
	
    motorHandler (int pina1, int pina2, int pina3, int pina4);
    motorHandler (int pina1, int pina2, int pina3, int pina4,
                  int pinb1, int pinb2, int pinb3, int pinb4);
    motorHandler (int pina1, int pina2, int pina3, int pina4,
                  int pinb1, int pinb2, int pinb3, int pinb4,
                  int pinc1, int pinc2, int pinc3, int pinc4);
    motorHandler (int pina1, int pina2, int pina3, int pina4,
                  int pinb1, int pinb2, int pinb3, int pinb4,
                  int pinc1, int pinc2, int pinc3, int pinc4,
                  int pind1, int pind2, int pind3, int pind4);
    motorHandler (int pina1, int pina2, int pina3, int pina4,
                  int pinb1, int pinb2, int pinb3, int pinb4,
                  int pinc1, int pinc2, int pinc3, int pinc4,
                  int pind1, int pind2, int pind3, int pind4,
                  int pine1, int pine2, int pine3, int pine4);
    motorHandler (int pina1, int pina2, int pina3, int pina4,
                  int pinb1, int pinb2, int pinb3, int pinb4,
                  int pinc1, int pinc2, int pinc3, int pinc4,
                  int pind1, int pind2, int pind3, int pind4,
                  int pine1, int pine2, int pine3, int pine4,
                  int pinf1, int pinf2, int pinf3, int pinf4);
    motorHandler (int pina1, int pina2, int pina3, int pina4,
                  int pinb1, int pinb2, int pinb3, int pinb4,
                  int pinc1, int pinc2, int pinc3, int pinc4,
                  int pind1, int pind2, int pind3, int pind4,
                  int pine1, int pine2, int pine3, int pine4,
                  int pinf1, int pinf2, int pinf3, int pinf4,
                  int ping1, int ping2, int ping3, int ping4);
    motorHandler (int pina1, int pina2, int pina3, int pina4,
                  int pinb1, int pinb2, int pinb3, int pinb4,
                  int pinc1, int pinc2, int pinc3, int pinc4,
                  int pind1, int pind2, int pind3, int pind4,
                  int pine1, int pine2, int pine3, int pine4,
                  int pinf1, int pinf2, int pinf3, int pinf4,
                  int ping1, int ping2, int ping3, int ping4,
                  int pinh1, int pinh2, int pinh3, int pinh4);
                  

                  
};


class msgReceiver
{
    public:

        String buf;
        JsonVariant root;
		HardwareSerial* serial;

        msgReceiver(HardwareSerial* serial_);
        int receiver();
        int understand(motorHandler motorHandler_); //specific for the pc serial
		int receiveCyclic();
    
    protected:

        StaticJsonBuffer<2000> jsonBuffer_;
    
};



#endif
