#include "print.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }
  initMaster();

  while(!connectMac(MAC_2)){
    //Serial.println("connecting");
    delay(1000);
  }
}

void loop() {
  printRssiForProcessing(MAC_2);
  delay(2000);
}
