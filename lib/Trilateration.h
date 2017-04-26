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

float getRssi(String mac)
{
  
  String rssi;
  int counter, i=0;
  float average = 0;

  counter = 0;

  mySerial.print("AT+CON" + mac);
  getSerialString();


  
 Serial.print(" ");
  
  for(i=0; i<PRECISION; i++){
    
    mySerial.print("AT+RSSI?");
    delay(200);
    rssi = getSerialString().substring(7,10);
    if(rssi.toInt() < 0)
    {
      average = (average*counter - rssi.toInt())/(counter+1);
      counter++;
    }
    else
    {
      delay(200);
      mySerial.print("AT+CON" + mac);
      getSerialString();
    }
  }
  
  
  mySerial.print("AT");
  delay(200);
  getSerialString();

  return(average);
}

float calculateDistance(float rssi)
{
  return(pow(10, (rssi-TX_POWER)/(10*FACTEUR)));
}

float getDistance(String mac)
{
  return(calculateDistance(getRssi(mac)));
  
}

void printDistance(String mac)
{
  int i;
 Serial.print("| ");
 Serial.print(mac);
 Serial.print(getDistance(mac));
 Serial.println(" m  |");
  for(i=0; i< 26+PRECISION; i++)
  {
   Serial.print("-");
  }
  Serial.println();
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

void printForProcessingSketch(){

  float d = getDistance(MAC_1);
  Serial.print(X1);
  Serial.print("|");
  Serial.print(Y1);
  Serial.print("|");
  Serial.println(d);

  d = getDistance(MAC_2);
  Serial.print(X2);
  Serial.print("|");
  Serial.print(Y2);
  Serial.print("|");
  Serial.println(d);

  d = getDistance(MAC_3);
  Serial.print(X3);
  Serial.print("|");
  Serial.print(Y3);
  Serial.print("|");
  Serial.println(d);
}

