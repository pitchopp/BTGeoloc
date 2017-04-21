#include "C:\Showcase\BTGeoloc\lib\functions.h"

void setup() {
  Serial.begin(9600);
  while (!Serial){
    
  }
  
  initSlave();
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
