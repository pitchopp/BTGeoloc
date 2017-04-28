#include "dataCollect.h"
#include <EEPROM.h>
int i;
void setup() {
  Serial.begin(9600);
  while(!Serial){
  }
  initMaster();
  int b[NB+1];
  for (i=0;i<NB+1;i++){
    b[i] = 0;
  }

  getRssiDistribution(b, 20000, MAC_2);
  for (i=0;i<NB+1;i++){
    if(b[i] > 0){
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(b[i]);
    }
  }
  
}

void loop() {
  
}
