#include <SoftwareSerial.h>
#include <math.h>
#include "config.h"

SoftwareSerial mySerial(RX_ARDUINO, TX_ARDUINO);
	

void initMaster()
{
  int i;
	
	mySerial.begin(9600);
	
	Serial.println("Setting hm-10 Master...");
	delay(1000);
	mySerial.print("AT");
	delay(500);
	Serial.println(mySerial.readString());
	
	mySerial.print("AT+RENEW");
	delay(500);
	Serial.println(mySerial.readString());
	
	mySerial.print("AT+RESET");
	delay(500);
	Serial.println(mySerial.readString());
	
	mySerial.print("AT+NAMEMaster");
	delay(500);
	Serial.println(mySerial.readString());
   mySerial.print("AT+MODE1");
   delay(500);
  Serial.println(mySerial.readString());
  
  mySerial.print("AT+IMME1");
  delay(500);
  Serial.println(mySerial.readString());
  
	mySerial.print("AT+ROLE1");
	delay(500);
	Serial.println(mySerial.readString());

  mySerial.print("AT+RESET");
  delay(500);
  Serial.println(mySerial.readString());
  	
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



float getRSSI(String mac)
{
  
  String rssi;
  int counter, i;
  float average = 0;

  counter = 0;

  mySerial.print("AT+CON" + mac);
  delay(200);
  rssi = mySerial.readString();

  Serial.print(" ");
  
  for(i=0; i<PRECISION; i++){
    
    mySerial.print("AT+RSSI?");
    //delay(200);
    rssi = mySerial.parseInt();
    
    if(rssi.toInt() < 0)
    {
      Serial.print("-");
      average = (average*counter - rssi.toInt())/(counter+1);
      counter++;
    }
    else
    {
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
  return(calculateDistance(getRSSI(mac)));
  
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


