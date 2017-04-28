#include <SoftwareSerial.h>
#include "config.h"


SoftwareSerial mySerial(RX_ARDUINO, TX_ARDUINO);

String getSerialString(){
  char c;
  int i=0;
  String s = "";
  while(!mySerial.available() && i<100){
    delay(10);
    i++;
  }
  delay(100);
  while(mySerial.available()){
    c = mySerial.read();
    s += c;
  }
  return s;
}

void initMaster()
{
  int i;
  
  mySerial.begin(9600);
  
  delay(1000);
  mySerial.print("AT");
  
  
  mySerial.print("AT+RENEW");
  getSerialString();
  
  mySerial.print("AT+RESET");
  getSerialString();
  
  mySerial.print("AT+NAMEMaster");
  getSerialString();
  
   mySerial.print("AT+MODE1");
   getSerialString();
  
  mySerial.print("AT+IMME1");
  getSerialString();
  
  mySerial.print("AT+ROLE1");
  getSerialString();

  mySerial.print("AT+RESET");
  getSerialString();
  
}

int getRssi(String mac)
{
  
  String rssi;
  int counter, i=0;
  float average = 0;

  counter = 0;

  mySerial.print("AT+CON" + mac);
  getSerialString();

    mySerial.print("AT+RSSI?");
    delay(200);
    rssi = getSerialString().substring(7,10);

    while(rssi.toInt() >= 0)
    {
      mySerial.print("AT");
  	  getSerialString();
  	  mySerial.print("AT");
  	  getSerialString();
      mySerial.print("AT+CON" + mac);
      getSerialString();
      
    }
  
  mySerial.print("AT");
  getSerialString();

  return(-(rssi.toInt()));
}

void printRssi(String mac){
  int i;
  
  digitalWrite(LED, HIGH);
 Serial.print("| ");
 Serial.print(mac);
 Serial.print(getRssi(mac));
 Serial.println(" m  |");
  for(i=0; i< 26+PRECISION; i++)
  {
   Serial.print("-");
  }
 Serial.println();
}

void getRssiDistribution(int a[], int n, String mac){
  int i;
  for(i=0; i<n; i++){
    int rssi = 70;
    if (rssi < NB && rssi >= 0){
      a[rssi] = a[rssi]+1;
      a[NB] = a[NB] + 1;
    }
  }
  
  
}
