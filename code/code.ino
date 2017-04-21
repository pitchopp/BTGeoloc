#include "functions.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }
  
  initMaster();

  
  
}

void loop() {
  //if(digitalRead(BUTTON) == LOW){
  delay(1000);
  printDistance(MAC_2);
  //}
}

