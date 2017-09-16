ri#include <EEPROM.h>
#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int i,n,panjang,maling=0;
const int button_reset = 41;
const int button_mati = 40;
const int button_hidup = 38;
const int indicator_off = 23;
const int indicator_on = 25;
const int bl = 13;

const int reed_depan = 27;
const int but_kipas_depan = 29;
const int but_lampu_depan = 31;
const int reed_kamar= 33;
const int but_kipas_kamar = 35;
const int but_lampu_kamar = 37;

const int but_kipas_dapur = 53;
const int but_lampu_dapur = 51;

const int reed_switch = 36;  
const int buzzer = 52; //ganti jadi pin interrupt

const int lampu_depan = 42;
const int lampu_kamar = 43;
const int lampu_dapur = 48;

const int kipas_depan = 44;
const int kipas_kamar = 45;
const int kipas_dapur = 46;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
  
  byte rowPins[ROWS] = {34, 32, 30, 28}; //connect to the row pinouts of the keypad 22, 24, 26, 28
  byte colPins[COLS] = {26, 24, 22}; //connect to the column pinouts of the keypad 30, 32, 34
  Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
  
Servo pintu_depan;  // create servo object to control a servo
Servo pintu_kamar;  // create servo object to control a servo
Servo pintu_dapur;  // create servo object to control a servo

int kipas_depan_status, lampu_depan_status,kipas_kamar_status, lampu_kamar_status, kipas_dapur_status, lampu_dapur_status  = 0;     // variable for reading the pin status
int kolom_lcd = 0, counter = 0, benar = 0; 
int alarm = 0, cek_alarm = 1, cek_alarm1 = 1, cek_alarm2 = 1, pos, reset_status, buka_status, tutup_status, kond = 0;    // variable to store the servo position
char command, key;
String string, string_keypad, g, pin, pass_baru;
bool stat_lampu_depan = false, 
     stat_kipas_depan = false, 
     stat_lampu_kamar = false, 
     stat_kipas_kamar = false, 
     stat_lampu_dapur = false, 
     stat_kipas_dapur = false, 
     stat_alarm = false,
     stat_pintu_depan = false;
long OnTime = 60000, send_time = 1000;
long scroll = 10000;
unsigned long last_key = 0, last_send = 0;


String str1 = ">>> Home is SECURED <<<";  // using a constant String
String str2 = ">>> Alarm is OFF <<<";
String strClear = "                ";
long previousMillis = 0;        // will store last time LCD was updated
long interval = 300;           // interval at which to update LCD (milliseconds)



void setup() {
  Serial.begin (9600);
 /* EEPROM.write(0,1);
  EEPROM.write(1,1); */
  str1 = str1 + strClear;
  str2 = str2 + strClear;
  tutup_pintu(1);
  //Serial.println( "Read float from EEPROM: " );    
  panjang = EEPROM.read(0);
  for (i = 1; i<= panjang; i++) g+=EEPROM.read(i);
    //Serial.println( g ); 
 
  lcd.begin(16, 2); //declare resolusi LCD
  pinMode(lampu_depan, OUTPUT);
  pinMode(lampu_kamar, OUTPUT);
  pinMode(lampu_dapur, OUTPUT);

  pinMode(kipas_depan, OUTPUT);
  pinMode(kipas_kamar, OUTPUT);
  pinMode(kipas_dapur, OUTPUT);

  pinMode(bl, OUTPUT);
  
  pinMode(button_reset, INPUT);
  pinMode(button_mati, INPUT);
  pinMode(button_hidup, INPUT);
  pinMode(reed_switch, INPUT);


  pinMode(reed_depan, INPUT);
  pinMode(but_kipas_depan,INPUT);
  pinMode(but_lampu_depan, INPUT);
  pinMode(reed_kamar, INPUT);
  pinMode(but_kipas_kamar, INPUT);
  pinMode(but_lampu_kamar, INPUT);
  pinMode(but_kipas_dapur, INPUT);
  pinMode(but_lampu_dapur, INPUT);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  digitalWrite(bl, HIGH);

  pintu_depan.attach(39);  // attaches the servo on pin 9 to the servo object
  //pintu_kamar.attach();  // attaches the servo on pin 9 to the servo object
  //pintu_dapur.attach();  // attaches the servo on pin 9 to the servo object

  pinMode(indicator_on, OUTPUT);
  pinMode(indicator_off, OUTPUT);
  

}

void buka_pintu(int i)
{
  if (i==1)
  {
    stat_pintu_depan == true;
   // Serial.print("111#");
    for (pos = 0; pos <= 70; pos += 3) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
         pintu_depan.write(pos);              // tell servo to go to position in variable 'pos'
         delay(15);                       // waits 15ms for the servo to reach the position 
         
    }
  digitalWrite(indicator_on, LOW);
  digitalWrite(indicator_off, HIGH);
  }
}

void tutup_pintu(int i)
{
  if (i==1)
  {
    stat_pintu_depan == false;
   // Serial.println("110#");
    for (pos = 70; pos >= 0; pos -= 3) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
         pintu_depan.write(pos);              // tell servo to go to position in variable 'pos'
         delay(15);                       // waits 15ms for the servo to reach the position 
    }
          digitalWrite(indicator_on, HIGH);
          digitalWrite(indicator_off, LOW);
      }
}

void lampu_nyala(int i)
{
  if (i==1) { digitalWrite(lampu_depan, HIGH);
  //Serial.println("211#");
  }
  if (i==2) { digitalWrite(lampu_kamar, HIGH);
  //Serial.println("221#");
  }
  if (i==3) { digitalWrite(lampu_dapur, HIGH);
  //Serial.println("231#");
  }
}

void lampu_mati(int i)
{
  if (i==1) { digitalWrite(lampu_depan, LOW); 
  //Serial.println("210#");
  }
  if (i==2) { digitalWrite(lampu_kamar, LOW);
  //Serial.println("220#");
  }
  if (i==3) { digitalWrite(lampu_dapur, LOW);
  //Serial.println("230#");
  }
}

void kipas_nyala(int i)
{
  if (i==1) { digitalWrite(kipas_depan, HIGH); 
  //Serial.println("311#");
  }
  if (i==2) { digitalWrite(kipas_kamar, HIGH); 
  //Serial.println("321#");
  }
  if (i==3) { digitalWrite(kipas_dapur, HIGH);
  //Serial.println("331#");
  }
}

void kipas_mati(int i)
{
  if (i==1) { digitalWrite(kipas_depan, LOW); 
  //Serial.println("310#");
  }
  if (i==2) { digitalWrite(kipas_kamar, LOW);
  //Serial.println("320#");
  }
  if (i==3) { digitalWrite(kipas_dapur, LOW); 
  //Serial.println("330#");
  }
}

void alarm_nyala() 
{ 
         digitalWrite(buzzer, HIGH);
         if (maling == 0){
          Serial.println("411#");
          stat_alarm = true;
          maling = 1;          
         }
         
         
        // Serial.println("alrm on");
         /*delay(50);   
         digitalWrite(buzzer, LOW);
         delay(50);*/    
}

void alarm_mati() 
{ 
         digitalWrite(buzzer, LOW);
         //Serial.println("410#");
         stat_alarm = false;
         maling = 0;
         
         //Serial.println("alrm off");
         /*delay(500);   
         digitalWrite(buzzer, LOW);
         delay(500);*/    
}

int cek_pass(String password){
  if (password == g){//compare string sama yg d simpen di eeprom
    return 1;
  }
  else{
    return 0;
  }
}

void old_pass(){
      string_keypad ="";
      
      lcd.clear();
      lcd.setCursor(0, 0); // set the cursor to column 0, line 1 
      lcd.print("old password:");
      key = keypad.getKey();
      while(key != '#'){
      key = keypad.getKey();
      if (key != NO_KEY && key != '#' && key != '*'){
        string_keypad += key;
        lcd.setCursor(kolom_lcd, 1); // set the cursor to column 0, line 1 
        lcd.print("*");
        //Serial.println(key);
        kolom_lcd++;//cek pass lama, ok masukkan pass baru
      }
    }
    kolom_lcd = 0;
    benar = cek_pass(string_keypad);
    if (benar == 1){
      lcd.clear();
      lcd.setCursor(0, 0); // set the cursor to column 0, line 1 
      lcd.print("password OK");
      delay(2000);
      lcd.clear();  
      new_pass();
    }
    else{
      lcd.clear();
      lcd.setCursor(0, 0); // set the cursor to column 0, line 1 
      lcd.print("wrong password");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0); // set the cursor to column 0, line 1 
      lcd.print("try again");
      delay(500);
      lcd.clear();  
          
      old_pass();
    }
}

void new_pass(){
      pass_baru="";
      lcd.clear();
      lcd.setCursor(0, 0); // set the cursor to column 0, line 1 
      lcd.print("Enter password:");
      key = keypad.getKey();
      pass_baru += key;
      while(key != '#'){
      key = keypad.getKey();
      if (key != NO_KEY && key != '#' && key != '*'){
        pass_baru += key;
        lcd.setCursor(kolom_lcd, 1); // set the cursor to column 0, line 1 
        lcd.print("*");
        //Serial.println(key);
        kolom_lcd++;//cek pass lama, ok masukkan pass baru
      }
    }
    kolom_lcd = 0;
    
      string_keypad="";
      lcd.clear();
      lcd.setCursor(0, 0); // set the cursor to column 0, line 1 
      lcd.print("Re-enter password:");
      key = keypad.getKey();
      string_keypad += key;
      while(key != '#'){
      key = keypad.getKey();
      if (key != NO_KEY && key != '#' && key != '*'){
        string_keypad += key;
        lcd.setCursor(kolom_lcd, 1); // set the cursor to column 0, line 1 
        lcd.print("*");
        //Serial.println(key);
        kolom_lcd++;//cek pass lama, ok masukkan pass baru
      }
    }
    kolom_lcd = 0;    
    if (string_keypad == pass_baru){
      lcd.clear();
      lcd.setCursor(0, 0); // set the cursor to column 0, line 1 
      lcd.print("password saved");
      last_key = millis();
      delay(2000);
      lcd.clear();
      pass_baru.remove(0, 1);
      simpan_eeprom(pass_baru);
  
    }
    else{
      lcd.clear();
      lcd.setCursor(0, 0); // set the cursor to column 0, line 1 
      lcd.print("wrong password");
      last_key = millis();
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0); // set the cursor to column 0, line 1 
      lcd.print("Try Again");
      delay(500);
      lcd.clear();      
      old_pass();
    }
  
}

void simpan_eeprom(String save)
{

  g =""; 
  EEPROM.write(0,save.length());
    for (i = 0; i< save.length(); i ++) { 
     n=(int)save[i]-48;
    EEPROM.write(i+1,n);
    g+=save[i];
          }  
  
 // Serial.println("Written float data type!"); Serial.println(g); 
lcd.clear();
      lcd.setCursor(0, 0); // set the cursor to column 0, line 1 
      lcd.print("Password saved");
  
}

void roll(){
  String str;
  for( ; ; ){
    lcd.clear();
    if (kond == 1){
    kond = 0;
    digitalWrite(bl, HIGH);
    break;
    
    }
    if (alarm == 0){
      str=str2;
    }
    else{
      str=str1;
    }
  
  
  int i;
  lcd.setCursor(16,0); 

  for (i = 0; i < str.length() ; ) {
    // wait without delay:
    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis > interval) {
      //update last LCD write
      previousMillis = currentMillis;   
      //Serial.println(str1.charAt(i));
      lcd.print(str.charAt(i));
      lcd.scrollDisplayLeft(); 
      i++;
    }
   //Do something else here, like check keypress events
  key = keypad.getKey();
  if (key != NO_KEY){
    kond = 1;
    last_key = millis();
    break;
    
  }
 reset_status = digitalRead(button_reset);  // read input value
  if (reset_status == HIGH) {         // check if the input is HIGH (button released)
   // Serial.println("reset");
    digitalWrite(bl, HIGH);
    
    old_pass(); 
    kond = 1;
    break;  
    //konfirm pass baru
    
    //reset EEPROM
  }
  
  tutup_status = digitalRead(button_mati);  // read input value
  if (tutup_status == HIGH) {         // check if the input is HIGH (button released)
    tutup_pintu(1);
    alarm=1;
    counter = 0;
    stat_pintu_depan = false;
    //Serial.println("Closed");
  }
  buka_status = digitalRead(button_hidup);  // read input value
  if (buka_status == HIGH) {         // check if the input is HIGH (button released)
    buka_pintu(1);
    alarm=0;
    alarm_mati();
    stat_pintu_depan = true;
    //Serial.println("410#");
    //Serial.println("Open");
  }
// BAGIAN INPUT DART PB BUAT KIPAS DAN LAMPU

// DEPAN
 kipas_depan_status  = digitalRead(but_kipas_depan);  
  if (kipas_depan_status == HIGH) {   
    if(stat_kipas_depan == false){
      kipas_nyala(1);
      stat_kipas_depan = true;
      delay(250);
       
    }
    else{
      kipas_mati(1);
      stat_kipas_depan = false;
        delay(250);
    }

  }
  lampu_depan_status  = digitalRead(but_lampu_depan);  
  if (lampu_depan_status == HIGH) {         
    if(stat_lampu_depan == false){
      lampu_nyala(1);
      stat_lampu_depan = true;
       delay(250);
    }
    else{
      lampu_mati(1);
      stat_lampu_depan = false;
        delay(250);
    }

  }

//KAMAR
 kipas_kamar_status  = digitalRead(but_kipas_kamar);  
  if (kipas_kamar_status == HIGH) {         
    if(stat_kipas_kamar == false){
      kipas_nyala(2);
      stat_kipas_kamar = true;
        delay(250);
    }
    else{
      kipas_mati(2);
      stat_kipas_kamar = false;
        delay(250);
    }

  }
  lampu_kamar_status  = digitalRead(but_lampu_kamar);  
  if (lampu_kamar_status == HIGH) {         
    if(stat_lampu_kamar == false){
      lampu_nyala(2);
      stat_lampu_kamar = true;
        delay(250);
    }
    else{
      lampu_mati(2);
      stat_lampu_kamar = false;
        delay(250);
    }

  }

//DAPUR
 kipas_dapur_status  = digitalRead(but_kipas_dapur);  
  if (kipas_dapur_status == HIGH) {         
    if(stat_kipas_dapur == false){
      kipas_nyala(3);
      stat_kipas_dapur = true;
        delay(250);
    }
    else{
      kipas_mati(3);
      stat_kipas_dapur = false;
        delay(250);
    }

  }
  lampu_dapur_status  = digitalRead(but_lampu_dapur);  
  if (lampu_dapur_status == HIGH) {         
    if(stat_lampu_dapur == false){
      lampu_nyala(3);
      stat_lampu_dapur = true;
        delay(250);
    }
    else{
      lampu_mati(3);
      stat_lampu_dapur = false;
        delay(250);
    }

  }
  

   //untuk alarm
  cek_alarm = digitalRead(reed_switch); // membaca kondisi reedswitch
  cek_alarm1 = digitalRead(reed_depan);
  cek_alarm2 = digitalRead(reed_kamar);
  if (alarm==1) // jika alarm nyala tapi pintu terbuka
  {

    if (cek_alarm==0||cek_alarm1==0||cek_alarm2==0) //
    {
    alarm_nyala();
    }
  }
  
  // buat menangkap password dari HP
  if (Serial.available() > 0) {string = "";
  while(Serial.available() > 0)
  {
      command = ((byte)Serial.read());     
      Serial.println(command);
      if(command == ':') { break;}
      else { string += command;}
      delay(1);
  }
  }
if (string!="") {Serial.println(string);}
  //mengecek perintah dari HP khusus untuk buka
  if(string == "depan_buka") {buka_pintu(1);
  alarm =0; alarm_mati(); stat_pintu_depan = true;
  //Serial.println("410#");
  counter = 0;} 


  if(string == "depan_nyala") {lampu_nyala(1); stat_lampu_depan = true;}
  if(string == "kamar_nyala") {lampu_nyala(2); stat_lampu_kamar = true;}
  if(string == "dapur_nyala") {lampu_nyala(3); stat_lampu_dapur = true;}
  
  if(string == "depan_mutar") {kipas_nyala(1); stat_kipas_depan = true;}
  if(string == "kamar_mutar") {kipas_nyala(2); stat_kipas_kamar = true;}
  if(string == "dapur_mutar") {kipas_nyala(3); stat_kipas_dapur = true;}

  //mengecek perintah dari HP khusus untuk tutup
  if(string == "depan_tutup") {tutup_pintu(1);
  alarm =1; counter = 0;stat_pintu_depan = false;}

  if(string == "depan_mati") {lampu_mati(1); stat_lampu_depan = false;}
  if(string == "kamar_mati") {lampu_mati(2); stat_lampu_kamar = false;}
  if(string == "dapur_mati") {lampu_mati(3); stat_lampu_dapur = false;}
  
  if(string == "depan_berhenti") {kipas_mati(1); stat_kipas_depan = false;}
  if(string == "kamar_berhenti") {kipas_mati(2); stat_kipas_kamar = false;}
  if(string == "dapur_berhenti") {kipas_mati(3); stat_kipas_dapur = false;}
  string="";


  currentMillis = millis();
  
  if(currentMillis - last_send >= send_time){
     //>>>>>>>>>>>>>>>>>>>sendcode here<<<<<<<<<<<<<<<,
     if(stat_alarm == true){
      Serial.print("*411");
     }
     else{
      Serial.print("*410");
     }
     if(stat_lampu_depan == true){
      Serial.print("211");
     }
     else{
      Serial.print("210");
     }

     if(stat_lampu_kamar == true){
      Serial.print("221");
     }
     else{
      Serial.print("220");
     }

     if(stat_lampu_dapur == true){
      Serial.print("231");
     }
     else{
      Serial.print("230");
     }

     if(stat_kipas_depan == true){
      Serial.print("311");
     }
     else{
      Serial.print("310");
     }

     if(stat_kipas_kamar == true){
      Serial.print("321");
     }
     else{
      Serial.print("320");
     }
     
     if(stat_kipas_dapur == true){
      Serial.print("331");
     }
     else{
      Serial.print("330");
     }

     if(stat_pintu_depan == false){
      Serial.println("110#");
     }
     else{
      Serial.println("111#");
     }
      currentMillis = millis();
     last_send = currentMillis;
  }
 
  }
   
  unsigned long currentMillis = millis();
  
  if(currentMillis - last_key >= OnTime){
     digitalWrite(bl, LOW);
  }
  //Do something else here, like check keypress events 
  }
  // clear screen for the next loop:
  lcd.clear();

  }
  



  
void loop() {
  lcd.setCursor(0, 0); // set the cursor to column 0, line 1 
  lcd.print("password:");
     
  //pengecekkan push button //
  reset_status = digitalRead(button_reset);  // read input value
  if (reset_status == HIGH) {         // check if the input is HIGH (button released)
    Serial.println("reset");
    digitalWrite(bl, HIGH);
    
    old_pass();   
    //konfirm pass baru
    
    //reset EEPROM
  } 
  tutup_status = digitalRead(button_mati);  // read input value
  if (tutup_status == HIGH) {         // check if the input is HIGH (button released)
    tutup_pintu(1);
    alarm=1;
    counter = 0;
    Serial.println("Closed");
  }
  buka_status = digitalRead(button_hidup);  // read input value
  if (buka_status == HIGH) {         // check if the input is HIGH (button released)
    buka_pintu(1);
    alarm=0;
   // Serial.println("410#");
    alarm_mati();
    Serial.println("Open");
  }
// BAGIAN INPUT DART PB BUAT KIPAS DAN LAMPU

// DEPAN
 kipas_depan_status  = digitalRead(but_kipas_depan);  
  if (kipas_depan_status == HIGH) {   
    if(stat_kipas_depan == false){
      kipas_nyala(1);
      stat_kipas_depan = true;
      delay(250);
       
    }
    else{
      kipas_mati(1);
      stat_kipas_depan = false;
        delay(250);
    }

  }
  lampu_depan_status  = digitalRead(but_lampu_depan);  
  if (lampu_depan_status == HIGH) {         
    if(stat_lampu_depan == false){
      lampu_nyala(1);
      stat_lampu_depan = true;
       delay(250);
    }
    else{
      lampu_mati(1);
      stat_lampu_depan = false;
        delay(250);
    }

  }

//KAMAR
 kipas_kamar_status  = digitalRead(but_kipas_kamar);  
  if (kipas_kamar_status == HIGH) {         
    if(stat_kipas_kamar == false){
      kipas_nyala(2);
      stat_kipas_kamar = true;
        delay(250);
    }
    else{
      kipas_mati(2);
      stat_kipas_kamar = false;
        delay(250);
    }

  }
  lampu_kamar_status  = digitalRead(but_lampu_kamar);  
  if (lampu_kamar_status == HIGH) {         
    if(stat_lampu_kamar == false){
      lampu_nyala(2);
      stat_lampu_kamar = true;
        delay(250);
    }
    else{
      lampu_mati(2);
      stat_lampu_kamar = false;
        delay(250);
    }

  }

//DAPUR
 kipas_dapur_status  = digitalRead(but_kipas_dapur);  
  if (kipas_dapur_status == HIGH) {         
    if(stat_kipas_dapur == false){
      kipas_nyala(3);
      stat_kipas_dapur = true;
        delay(250);
    }
    else{
      kipas_mati(3);
      stat_kipas_dapur = false;
        delay(250);
    }

  }
  lampu_dapur_status  = digitalRead(but_lampu_dapur);  
  if (lampu_dapur_status == HIGH) {         
    if(stat_lampu_dapur == false){
      lampu_nyala(3);
      stat_lampu_dapur = true;
        delay(250);
    }
    else{
      lampu_mati(3);
      stat_lampu_dapur = false;
        delay(250);
    }

  }
  
  // buat menangkap password dari keypad
  key = keypad.getKey();
  if (key != NO_KEY){
    //Serial.println(key);
    digitalWrite(bl, HIGH);
    last_key = millis();
    if (key == '#'){
      benar = cek_pass(string_keypad);
      if (benar == 1){
        buka_pintu(1);
        alarm = 0;
        //Serial.println("410#");
        alarm_mati();
        benar = 0;
        counter = 0;
        kolom_lcd = 0;
        string_keypad = "";
        lcd.clear();
        //Serial.println("benar");
      }
      else{
        counter++;
        kolom_lcd = 0;
        string_keypad = "";
        lcd.clear();
        //Serial.println("salah");
        //Serial.println("411#");
        alarm_nyala();
        delay(200);
        //Serial.println("410#");
        alarm_mati();
      }
    }
    else if (key == '*'){
      tutup_pintu(1);
      alarm =1;
      counter = 0;
      kolom_lcd = 0;
      string_keypad = "";
      lcd.clear();
      //Serial.println("tutup");
    }
    else{
      string_keypad += key;
      lcd.setCursor(kolom_lcd, 1); // set the cursor to column 0, line 1 
      lcd.print("*");
      kolom_lcd++;
    }
  }

  //Salah masukan pass 3X
  if (counter >= 3){
    //Serial.println("411#");
    alarm_nyala();
    //Serial.println("alarm");  
  }

  //untuk alarm
  cek_alarm = digitalRead(reed_switch); // membaca kondisi reedswitch
  cek_alarm1 = digitalRead(reed_depan);
  cek_alarm2 = digitalRead(reed_kamar);
  if (alarm==1) // jika alarm nyala tapi pintu terbuka
  {

    if (cek_alarm==0||cek_alarm1==0||cek_alarm2==0) //
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
  if(string == "depan_buka") {buka_pintu(1);
  alarm =0; alarm_mati(); //Serial.println("410#");
  counter = 0;} 

  if(string == "depan_nyala") {lampu_nyala(1); stat_lampu_depan = true;}
  if(string == "kamar_nyala") {lampu_nyala(2); stat_lampu_kamar = true;}
  if(string == "dapur_nyala") {lampu_nyala(3); stat_lampu_dapur = true;}
  
  if(string == "depan_mutar") {kipas_nyala(1); stat_kipas_depan = true;}
  if(string == "kamar_mutar") {kipas_nyala(2); stat_kipas_kamar = true;}
  if(string == "dapur_mutar") {kipas_nyala(3); stat_kipas_dapur = true;}

  //mengecek perintah dari HP khusus untuk tutup
  if(string == "depan_tutup") {tutup_pintu(1);
  alarm =1; counter = 0;}


  if(string == "depan_mati") {lampu_mati(1); stat_lampu_depan = false;}
  if(string == "kamar_mati") {lampu_mati(2); stat_lampu_kamar = false;}
  if(string == "dapur_mati") {lampu_mati(3); stat_lampu_dapur = false;}
  
  if(string == "depan_berhenti") {kipas_mati(1); stat_kipas_depan = false;}
  if(string == "kamar_berhenti") {kipas_mati(2); stat_kipas_kamar = false;}
  if(string == "dapur_berhenti") {kipas_mati(3); stat_kipas_dapur = false;} // 
  string="";

  unsigned long currentMillis = millis();
 
  if(currentMillis - last_send >= send_time){
     //>>>>>>>>>>>>>>>>>>>sendcode here<<<<<<<<<<<<<<<,
     if(stat_alarm == true){
      Serial.print("*411");
     }
     else{
      Serial.print("*410");
     }
     if(stat_lampu_depan == true){
      Serial.print("211");
     }
     else{
      Serial.print("210");
     }

     if(stat_lampu_kamar == true){
      Serial.print("221");
     }
     else{
      Serial.print("220");
     }

     if(stat_lampu_dapur == true){
      Serial.print("231");
     }
     else{
      Serial.print("230");
     }

     if(stat_kipas_depan == true){
      Serial.print("311");
     }
     else{
      Serial.print("310");
     }

     if(stat_kipas_kamar == true){
      Serial.print("321");
     }
     else{
      Serial.print("320");
     }
     
     if(stat_kipas_dapur == true){
      Serial.print("331");
     }
     else{
      Serial.print("330");
     }

     if(stat_pintu_depan == false){
      Serial.println("110#");
     }
     else{
      Serial.println("111#");
     }
      currentMillis = millis();
     last_send = currentMillis;
  } 
  
  if(currentMillis - last_key >= scroll){
     roll();
  }
}

