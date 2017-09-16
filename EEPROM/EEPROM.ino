#include <EEPROM.h>
int zz;
int EEsize = 10; // size in bytes of your board's EEPROM
 
void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  /*Serial.println("Writing random numbers...");
  for (int i = 0; i < EEsize; i++)
  {
    zz=random(255);
    EEPROM.write(i, zz);
  }*/
  //EEPROM.write(0, 22);
  zz = EEPROM.read(0);
  Serial.print("EEPROM position: ");
    Serial.print(0);
    Serial.print(" contains ");
    Serial.println(zz);
    delay(10000);
    /*
  for (int a=0; a<EEsize; a++)
  {
    zz = EEPROM.read(a);
    Serial.print("EEPROM position: ");
    Serial.print(a);
    Serial.print(" contains ");
    Serial.println(zz);
    delay(10000);
  }*/
}
void loop()
{
  
  Serial.println();
  
}
