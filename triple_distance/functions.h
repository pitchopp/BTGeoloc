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
	
	Serial.println("Setting hm-10 Master...");
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
  	
	Serial.println("Settings finished...");

  Serial.println();

  for(i=0; i< 26+PRECISION; i++)
  {
    Serial.print("-");
  }
  Serial.println();
  
  Serial.print("|  MAC Adress  ");
  
  for(i=0; i<PRECISION; i++)
  {
    Serial.print("-");
  }
  
  Serial.println(" Distance |");

  for(i=0; i< 26+PRECISION; i++)
  {
    Serial.print("-");
  }
  Serial.println();
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
    //rssi = mySerial.parseInt();
    rssi = getSerialString().substring(7,10);
    if(rssi.toInt() < 0)
    {
      Serial.print("-");
      average = (average*counter - rssi.toInt())/(counter+1);
      counter++;
    }
    else
    {
      delay(2000);
      mySerial.print("AT+CON" + mac);
      getSerialString();
      Serial.print("x");
    }
  }
  
  Serial.print("  ");
  
  
  mySerial.print("AT");

  delay(2000);

  return(average);
}

float calculateDistance(float rssi)
{
  return(pow(10, rssi/(10*FACTEUR))/1000);
}

float getDistance(String mac)
{
  //Serial.println("Getting distance from " + mac);
  //digitalWrite(LED, HIGH);
  return(calculateDistance(getRssi(mac)));
  
}

void printDistance(String mac)
{
  int i;
  
  digitalWrite(LED, HIGH);
  Serial.print("| ");
  Serial.print(mac);
  Serial.print(getDistance(mac));
  Serial.println(" m  |");
  for(i=0; i< 26+PRECISION; i++)
  {
    Serial.print("-");
  }
  Serial.println();
  digitalWrite(LED, LOW);
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
  digitalWrite(LED, LOW);
}

void printTripleDistance(){
  delay(2000);
  printDistance(MAC_1);
  delay(2000);
  printDistance(MAC_2);
  delay(2000);
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


