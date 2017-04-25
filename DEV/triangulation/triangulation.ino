#include "C:\Showcase\BTGeoloc\lib\functions.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }

  initMaster();
}

void loop() {
  
  /*printCoordinates(
    getDistance(MAC_1),
    getDistance(MAC_2),
    getDistance(MAC_3));*/
  printTripleDistance();
}

