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
  delay(200);
  while(mySerial.available()){
    c = mySerial.read();
    s += c;
  }
  //Serial.println(s);
  return s;
}

void initMaster()
{
  int i;
  
  mySerial.begin(9600);
  Serial.println("Settings");
  delay(1000);
  mySerial.print("AT");
  delay(1000);
  
  
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

  Serial.println("DONE");
}

int getRssi(String mac)
{
  
  String rssi;
  int counter, i=0;

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

bool connectMac(String mac){
  mySerial.print("AT+CON" + mac);
  String response = getSerialString();
  mySerial.print("AT+RSSI?");
  response = getSerialString();
  return (response.substring(0,2) == "OK");
}


void getRssiDistribution(int a[], int n, String mac){
  
  String s;
  int i, rssi;
  
  while(!connectMac(mac)){
    Serial.println("reconnecting");
    delay(1000);
  }
    for(i=0; i<n; i++){
      
    mySerial.print("AT+RSSI?");
    s = getSerialString().substring(7,10);
    rssi = -s.toInt();
    Serial.println(i);
      if (rssi < NB && rssi >= 0){
        a[rssi] = a[rssi]+1;
        a[NB] = a[NB] + 1;
      }
    }
}
