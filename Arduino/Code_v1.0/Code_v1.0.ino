#include "iGEM-Madrid-OLM.h"

msgReceiver serial (&Serial);
msgReceiver serial2 (&Serial2);

motorHandler motorHandler_( 38, 42, 40, 44,
                            46, 50, 48, 52,
                            47, 51, 49, 53,
                            18, 20, 19, 21,
                            22, 26, 24, 28,
                            30, 34, 32, 36  ,
                            31, 35, 33, 37,
                            39, 43, 41, 45);

void setup() {

  //PC-Arduino
  Serial.begin(115200);
  //Arduino-rodeostat
  Serial2.begin(115200);

}

void loop() {
  // Handle the motors
  motorHandler_.runMotors(); 

}

void serialEvent() {
  if (serial.receiver() != 0)
    Serial.println("ERROR:  There was a problem parsing the string");

  serial.understand(motorHandler_);

}

void serialEvent2() {
  delay(5);

  if (serial2.receiver() != 0)
    Serial.println("ERROR:  There was a problem receiving rodeostat message");

  String msg = serial2.root[1];
  serial2.root.printTo(Serial);
  Serial.println(msg); 
}

