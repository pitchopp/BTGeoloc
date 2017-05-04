#include "print.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }
  initMaster();

  while(!connectMac(mac)){
    delay(1000);
  }
}

void loop() {
  printRssiForProcessing();
}
