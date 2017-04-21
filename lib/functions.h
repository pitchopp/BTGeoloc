#include <SoftwareSerial.h>
#include <math.h>
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
  
 // Serial.println("Setting hm-10 Master...");
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
    
 // Serial.println("Settings finished...");

 // Serial.println();

  for(i=0; i< 26+PRECISION; i++)
  {
   // Serial.print("-");
  }
 // Serial.println();
  
 // Serial.print("|  MAC Adress  ");
  
  for(i=0; i<PRECISION; i++)
  {
   // Serial.print("-");
  }
  
 // Serial.println(" Distance |");

  for(i=0; i< 26+PRECISION; i++)
  {
   // Serial.print("-");
  }
 // Serial.println();
}

void initSlave()
{
  mySerial.begin(9600);
  
  Serial.println("Setting hm-10 Slave...");

  delay(1000);
  mySerial.print("AT");
  delay(500);
  
  Serial.println(mySerial.readString());
  
  mySerial.print("AT+RENEW");
  delay(500);
  Serial.println(mySerial.readString());
  
  mySerial.print("AT+RESET");
  delay(1000);
  
  Serial.println(mySerial.readString());
  mySerial.print("AT+NAMESlave");
  delay(500);
  
  Serial.println(mySerial.readString());
  mySerial.print("AT+MODE1");
  delay(500);
  
  Serial.println(mySerial.readString());

  mySerial.print("AT+IMME1");
  delay(500);
  Serial.println(mySerial.readString());

  mySerial.print("AT+RESET");
  delay(500);
  
  Serial.println(mySerial.readString());
}






float getRssi(String mac)
{
  
  String rssi;
  int counter, i=0;
  float average = 0;

  counter = 0;

  mySerial.print("AT+CON" + mac);
  getSerialString();


  
 // Serial.print(" ");
  
  for(i=0; i<PRECISION; i++){
    
    mySerial.print("AT+RSSI?");
    delay(200);
    //rssi = mySerial.parseInt();
    rssi = getSerialString().substring(7,10);
    if(rssi.toInt() < 0)
    {
     // Serial.print("-");
      average = (average*counter - rssi.toInt())/(counter+1);
      counter++;
    }
    else
    {
      delay(2000);
      mySerial.print("AT+CON" + mac);
      getSerialString();
     // Serial.print("x");
    }
  }
  
 // Serial.print("  ");
  
  
  mySerial.print("AT");

  delay(2000);
 // Serial.println(average);
  return(average);
}

float calculateDistance(float rssi)
{
  return(pow(10, (rssi-TX_POWER)/(10*FACTEUR)));
}

float getDistance(String mac)
{
  //Serial.println("Getting distance from " + mac);
  //digitalWrite(LED, HIGH);
  float d = calculateDistance(getRssi(mac));
 // Serial.println(d);
  return(d);
  
}

void printDistance(String mac)
{
  int i;
  
  //digitalWrite(LED, HIGH);
 // Serial.print("| ");
 // Serial.print(mac);
 Serial.println(getDistance(mac));
 // Serial.println(" m  |");
  for(i=0; i< 26+PRECISION; i++)
  {
   // Serial.print("-");
  }
 // Serial.println();
  //digitalWrite(LED, LOW);
}

void printRssi(String mac){
  int i;
  
  digitalWrite(LED, HIGH);
 // Serial.print("| ");
 // Serial.print(mac);
 // Serial.print(getRssi(mac));
 // Serial.println(" m  |");
  for(i=0; i< 26+PRECISION; i++)
  {
   // Serial.print("-");
  }
 // Serial.println();
  digitalWrite(LED, LOW);
}

void printTripleDistance(){
  delay(1000);
  printDistance(MAC_1);
  delay(1000);
  printDistance(MAC_2);
  delay(1000);
  printDistance(MAC_3);
}

void printTripleRssi(){
  delay(2000);
  printRssi(MAC_1);
  delay(2000);
  printRssi(MAC_2);
  delay(2000);
  printRssi(MAC_3);
}



float A = 2*(X2 - X1);
float B = 2*(Y2 - Y1);

float D = 2*(X3 - X2);
float E = 2*(Y3 - Y2);


float getX(float d1, float d2, float d3){

  float C = d1*d1 - d2*d2 - X1*X1 + X2*X2 - Y1*Y1 + Y2*Y2;
  float F = d2*d2 - d3*d3 - X2*X2 + X3*X3 - Y2*Y2 + Y3*Y3;

  return (C*E - F*B)/(A*E - B*D);
  
}

float getY(float d1, float d2, float d3){

  float C = d1*d1 - d2*d2 - X1*X1 + X2*X2 - Y1*Y1 + Y2*Y2;
  float F = d2*d2 - d3*d3 - X2*X2 + X3*X3 - Y2*Y2 + Y3*Y3;

  return (A*F - C*D)/(A*E - B*D);
  
}

void printCoordinates(float d1, float d2, float d3){

  Serial.print("X : ");
  Serial.println(getX(d1,d2,d3));
  Serial.print("Y : ");
  Serial.println(getY(d1,d2,d3));
  
}

