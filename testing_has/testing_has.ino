#include <EEPROM.h>

int i,n,panjang;

String string, string_keypad, g, pin, pass_baru;

void setup() {
  Serial.begin (9600);
  simpan_eeprom("1230");
 // for (int i = 0; i < 4; i++) g+= EEPROM.read(i);
 // Serial.println(g); 
}

void simpan_eeprom(String save)
{
  Serial.println(save.length());

    for (i = 1; i< save.length(); i += 1) { 
     n = (int)save[i]-48;
   Serial.println(n);
    g+=save[i];
          }  
}

  
void loop() {

}

