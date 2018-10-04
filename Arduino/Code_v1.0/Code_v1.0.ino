#include "iGEM-Madrid-OLM.h"

msgReceiver serial;
motorHandler motorHandler_(4076,8,9,10,11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void serialEvent() {
  
 delay(50);
  
 if (serial.receiver() == ERR_PARS)
    Serial.println("ERROR:  There was a problem parsing the string");
 
 serial.understand(motorHandler_);
}
