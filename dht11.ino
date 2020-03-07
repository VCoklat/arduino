#include <dht.h>

dht DHT;

#define DHT11_PIN 7

void setup(){
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  Serial.print("Motion = ");
  Serial.println(digitalRead(A0));
  if (digitalRead(A0) == HIGH){
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  delay(2000);
}
