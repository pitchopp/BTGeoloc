#include "dataCollect.h"
#include <EEPROM.h>
int i;
void setup() {
  Serial.begin(9600);
  while(!Serial){
  }
  //initMaster();
  int b[NB+1];
  for (i=0;i<NB+1;i++){
    b[i] = 0;
  }
  getRssiDistribution(b, 3, MAC_1);
  for (i=0;i<NB+1;i++){
    Serial.print(b[i]);
    Serial.print("|");
  }
  Serial.println();
}

void loop() {
  
}
