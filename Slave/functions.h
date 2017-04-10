#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9);
  
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

