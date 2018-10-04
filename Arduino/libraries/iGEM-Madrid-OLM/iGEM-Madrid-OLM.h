#ifndef IGEM_MADRID_OLM
#define IGEM_MADRID_OLM

#include <Arduino.h>
#include <ArduinoJson.h>
#include <AccelStepper.h>

#define ERR_PARS 1



class motorHandler
{

    public:
    
    AccelStepper** motors;
    int motorNumber;
    
    motorHandler ();
    motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4);
    motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                  int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4);
    motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                  int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4,
                  int stepsPerRevc, int pinc1, int pinc2, int pinc3, int pinc4);
    motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                  int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4,
                  int stepsPerRevc, int pinc1, int pinc2, int pinc3, int pinc4,
                  int stepsPerRevd, int pind1, int pind2, int pind3, int pind4);
    motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                  int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4,
                  int stepsPerRevc, int pinc1, int pinc2, int pinc3, int pinc4,
                  int stepsPerRevd, int pind1, int pind2, int pind3, int pind4,
                  int stepsPerReve, int pine1, int pine2, int pine3, int pine4);
    motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                  int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4,
                  int stepsPerRevc, int pinc1, int pinc2, int pinc3, int pinc4,
                  int stepsPerRevd, int pind1, int pind2, int pind3, int pind4,
                  int stepsPerReve, int pine1, int pine2, int pine3, int pine4,
                  int stepsPerRevf, int pinf1, int pinf2, int pinf3, int pinf4);
    motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                  int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4,
                  int stepsPerRevc, int pinc1, int pinc2, int pinc3, int pinc4,
                  int stepsPerRevd, int pind1, int pind2, int pind3, int pind4,
                  int stepsPerReve, int pine1, int pine2, int pine3, int pine4,
                  int stepsPerRevf, int pinf1, int pinf2, int pinf3, int pinf4,
                  int stepsPerRevg, int ping1, int ping2, int ping3, int ping4);
    motorHandler (int stepsPerReva, int pina1, int pina2, int pina3, int pina4,
                  int stepsPerRevb, int pinb1, int pinb2, int pinb3, int pinb4,
                  int stepsPerRevc, int pinc1, int pinc2, int pinc3, int pinc4,
                  int stepsPerRevd, int pind1, int pind2, int pind3, int pind4,
                  int stepsPerReve, int pine1, int pine2, int pine3, int pine4,
                  int stepsPerRevf, int pinf1, int pinf2, int pinf3, int pinf4,
                  int stepsPerRevg, int ping1, int ping2, int ping3, int ping4,
                  int stepsPerRevh, int pinh1, int pinh2, int pinh3, int pinh4);
                  
    int adjustMotor (int motor, int speed_, int steps_);
    int adjustMotor (int motor, int steps_);
                  
};


class msgReceiver
{
    public:

        String buf;
        JsonVariant root;

        msgReceiver();
        int receiver();
        int understand(motorHandler motorHandler_);
    
    protected:

        StaticJsonBuffer<200> jsonBuffer_;
    
};



#endif
