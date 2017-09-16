#include <EEPROM.h>
#include <Keypad.h>
#include <Servo.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {8, 7, 6, 5}; 
byte colPins[COLS] = {4, 3, 2}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

Servo pintu;                    // (+-)

const int reset_indicator = 10;   // (-)
const int alarm_indicator = 11; // (-)
const int buzzer = 12;          // (-)
const int lamp = 13;            // (-)

const int ldr = A0;             // (+-)
const int reed = A1;            // (+-)
const int buka = A2;            // (+-)
const int tutup = A3;           //
const int reset = A4;           // (+-)
const int buzzer2 = A5;

// VAR
String string_keypad, pass_baru, string, g;//g="1234";
char key, command;
int benar, pos, reset_status, buka_status, tutup_status, panjang, alarm = 0, counter = 0, cek_alarm = 0;

// VAR

// FUNCTION

void alarm_nyala2(){ 
         digitalWrite(buzzer2, HIGH);
        // Serial.println("alrm on");  
}

void alarm_mati2() { 
         digitalWrite(buzzer2, LOW);
         //Serial.println("alrm off");
}

void new_pass(){
      digitalWrite(reset_indicator, HIGH);
      pass_baru="";
      key = keypad.getKey();
      pass_baru += key;
      while(key != '#'){
      key = keypad.getKey();
      if (key != NO_KEY && key != '#' && key != '*'){
        pass_baru += key;
        alarm_nyala2();
        delay(100);
        alarm_mati2();
        //Serial.println(key);
        }
      }
      pass_baru.trim();
      //EEPROM.put(0, pass_baru);
      g =""; 
      EEPROM.write(0,(pass_baru.length()-1));
      for (int i = 1; i< pass_baru.length(); i ++) { 
         int n=(int)pass_baru[i]-48;
         EEPROM.write(i,n);
         g+=pass_baru[i];
        //g+= EEPROM.read(i);
      }  
      digitalWrite(reset_indicator, LOW);
}

int cek_pass(String password){
  panjang = EEPROM.read(0);
  g="";
  for (int i = 1; i<= panjang; i++) g+=EEPROM.read(i);
  Serial.println("Ini g yg dibandingin");
  Serial.println(g);
  if (password == g){   //compare string sama yg d simpen di eeprom
    return 1;
  }
  else{
    return 0;
  }
}

void buka_pintu() {
    for (pos = 0; pos <= 70; pos += 3) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
         pintu.write(pos);              // tell servo to go to position in variable 'pos'
         delay(15);                       // waits 15ms for the servo to reach the position 
    }
    digitalWrite(alarm_indicator, LOW);
    alarm_mati();
}

void tutup_pintu() {
    for (pos = 70; pos >= 0; pos -= 3) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
         pintu.write(pos);              // tell servo to go to position in variable 'pos'
         delay(15);                       // waits 15ms for the servo to reach the position 
    }
    digitalWrite(alarm_indicator, HIGH);
    alarm =1;
}

void alarm_nyala(){ 
         digitalWrite(buzzer, HIGH);
        // Serial.println("alrm on");  
}

void alarm_mati() { 
         digitalWrite(buzzer, LOW);
         //Serial.println("alrm off");
}

// FUNCTION

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pintu.attach(9);
  pinMode(reset_indicator, OUTPUT);
  pinMode(alarm_indicator, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(lamp, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(reed, INPUT);
  digitalWrite(reed, HIGH);
  pinMode(buka, INPUT);
  digitalWrite(buka, HIGH);
  pinMode(tutup, INPUT);
  digitalWrite(tutup, HIGH);
  pinMode(reset, INPUT);
  digitalWrite(reset, HIGH);
  tutup_pintu();
  buka_pintu();
  //panjang = EEPROM.read(0);
  //for (int i = 1; i<= panjang; i++) g+=EEPROM.read(i);
}

void loop() {
  if(string.length()>0) Serial.println(" ");
  string = "";
  char command;
  if (Serial.available() > 0)
  {
    while(Serial.available() > 0)
    {
      command = ((byte)Serial.read());
      string += command;
      delay(10);
    } 
    Serial.println(string);
  }
    
//pengecekkan push button //
  reset_status = digitalRead(reset);
  if (reset_status == LOW) {         // check if the input is HIGH (button released)
    Serial.println("reset");
    new_pass();   
  } 
  
  //bluetooth
  if (string=="close") {
    tutup_pintu();
    alarm=1;
    counter = 0;
    Serial.println("Closed");
  }

  if (string=="open") {
    buka_pintu();
    alarm=0;
    alarm_mati();
    Serial.println("Open");
  }
  //
  
  tutup_status = digitalRead(tutup);  // read input value
  if (tutup_status == LOW) {         // check if the input is HIGH (button released)
    tutup_pintu();
    alarm=1;
    counter = 0;
    Serial.println("Closed");
  }
  
  buka_status = digitalRead(buka);  // read input value
  if (buka_status == LOW) {         // check if the input is HIGH (button released)
    buka_pintu();
    counter = 0;
    alarm=0;
    alarm_mati();
    Serial.println("Open");
  }
  
  
// buat menangkap password dari keypad
  key = keypad.getKey();
  //Serial.println(key);
  if (key != NO_KEY){
    Serial.println(key);
    if (key == '#'){
      alarm_nyala2();
      delay(100);
      alarm_mati2();
      string_keypad.trim();
      benar = cek_pass(string_keypad);
      if (benar == 1){
        buka_pintu();
        alarm = 0;
        alarm_mati();
        benar = 0;
        counter = 0;
        string_keypad = "";
        //Serial.println("benar");
      }
      else{
        counter++;
        string_keypad = "";
        alarm_nyala();
        delay(200);
        alarm_mati();
      }
    }
    else if (key == '*'){
      alarm_nyala2();
      delay(100);
      alarm_mati2();
      tutup_pintu();
      alarm =1;
      counter = 0;
      string_keypad = "";
      //Serial.println("tutup");
    }
    else{
      string_keypad += key;
      alarm_nyala2();
      delay(100);
      alarm_mati2();
    }
  }

  //Salah masukan pass 3X
  if (counter >= 3){
    alarm_nyala();
  }

  //untuk door alarm
  cek_alarm = digitalRead(reed); // membaca kondisi reedswitch
  if (alarm==1) // jika alarm nyala tapi pintu terbuka
  {

    if (cek_alarm==1) //
    {
        alarm_nyala();
    }
  }
  
  // buat menangkap password dari HP
  if (Serial.available() > 0) {string = "";}
  while(Serial.available() > 0)
  {
      command = ((byte)Serial.read());     
      if(command == ':') { break;}
      else { string += command;}
      delay(1);
  }
if (string!="") {Serial.println(string);}
  //mengecek perintah dari HP khusus untuk buka
  if(string == "depan_buka") {buka_pintu();
  alarm =0; alarm_mati(); //Serial.println("410#");
  counter = 0;} 

  //mengecek perintah dari HP khusus untuk tutup
  if(string == "depan_tutup") {tutup_pintu();
  alarm =1; counter = 0;}
  string="";

// delay(1000);

int ldrStatus = analogRead(ldr);
//Serial.println(ldrStatus);
if (ldrStatus >= 100) {
digitalWrite(lamp, LOW);
}

else {
digitalWrite(lamp, HIGH);
}
 
}

