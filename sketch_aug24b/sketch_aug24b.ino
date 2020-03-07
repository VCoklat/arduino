void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(21,INPUT);
  pinMode(19,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int DigitalValue, Infrared;
  DigitalValue = digitalRead(21);
  //Serial.println(DigitalValue);
  if(DigitalValue==1) digitalWrite(13,HIGH); else digitalWrite(13,LOW);
  Infrared = digitalRead(19);
  Serial.println(Infrared);
  if(Infrared==1) digitalWrite(12,HIGH); else digitalWrite(12,LOW);

}
