
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("1.2|5.6|5.5");
  delay(1000);
  Serial.println("5|5|3");
  delay(1000);
}
