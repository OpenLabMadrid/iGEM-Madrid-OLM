#include "iGEM-Madrid-OLM.h"

msgReceiver serial;
msgReceiver serial2;

motorHandler motorHandler_(4076, 8, 9, 10, 11);

void setup() {

  //PC-Arduino
  Serial.begin(9600);
  //Arduino-rodeostat
  Serial2.begin(115200);

}

void loop() {
  // Handle the motors
  motorHandler_.runMotors();
}

void serialEvent() {
  delay(50);

  if (serial.receiver() != 0)
    Serial.println("ERROR:  There was a problem parsing the string");

  serial.understand(motorHandler_);
}

void SerialEvent2() {
  delay(5);

  if (serial.receiver() != 0)
    Serial.println("ERROR:  There was a problem receiving rodeostat message");

  String msg = "";
  serial2.root.printTo(msg);
  Serial.println(msg);
}

