#include "DHTesp.h"
long suhu,suhu_lama, kelembapan, kelembapan_lama,sama,i =0; 
String kalimat, kalimat_lama;
DHTesp dht;
int dhtPin = 23; 
void setup()
{
  Serial.begin(115200);
 
  dht.setup(dhtPin, DHTesp::DHT11);
}
 
void loop()
{
  if (i%5==0){
    Serial.println("");
    Serial.println("Kelembaban\tTemperatur\tTemperatur"); 
    Serial.println("    %  \t\tCelcius \tFahrenheit");
  }
  
  i=i+1;
  TempAndHumidity newValues = dht.getTempAndHumidity();
  kalimat =(String(newValues.humidity)+"\t" +"\t" + String(newValues.temperature)+"\t" +"\t" + String(newValues.temperature*9/5+32));
  
  if(kalimat_lama== kalimat){
    if(sama==0){
      Serial.println("");
    }
    if(sama<20) {
      Serial.print(".");}
    sama=sama+1;
    
  } else{
    Serial.println("");
    Serial.print(kalimat);
    sama=0;
  }
  kalimat_lama= kalimat;
 
  delay(5000);
 
}
