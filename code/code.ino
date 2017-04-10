#include "functions.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }
  
  initMaster();

  
  
}

void loop() {
  //if(digitalRead(BUTTON) == LOW){
  printDistance("5065831B35F8");
  delay(3000);
  //}
}

