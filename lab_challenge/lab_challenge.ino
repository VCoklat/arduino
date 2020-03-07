#include "SoftwareSerial.h"
int suhu,suhu_lama, kelembapan, kelembapan_lama,sama,i =0;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, INPUT); //kuning

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  sama=0;
  suhu = random(0, 2);
  kelembapan = random(0, 2);
  if (i%5==0){
    Serial.println("Kelembaban\tTemperatur\tTemperatur"); 
    Serial.println("    %  \t\tCelcius \tFahrenheit");
  }
  
  i=i+1;
  if ((suhu==suhu_lama)&&(kelembapan==kelembapan_lama)) 
  {
    if(sama<20) {Serial.print(".");}
    sama=sama+1;
  } else{
    Serial.println(String(kelembapan)+"\t" + String(suhu)+"\t" + String(suhu*9/5+32));
    suhu_lama=suhu;
    kelembapan_lama=kelembapan;
  }
}
