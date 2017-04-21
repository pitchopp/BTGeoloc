#include "functions.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }
  
  initMaster();

  
}

void loop() {
  printTripleDistance();
}

