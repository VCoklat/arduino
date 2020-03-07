#include <DallasTemperature.h>
#include <OneWire.h>

#include <Wire.h>
#include <Servo.h>
#include <Adafruit_INA219.h>
#include <SPI.h>
//#include "SdFat.h"
#include "SoftwareSerial.h"
//SdFat SD;

#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);
Adafruit_INA219 ina219;
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
String ssid ="GOLD DRAGON";

String password="jimmysan";
int matahari =0;
int ldr8 = 0;
int ldr7 = 0;
int ldr6 = 0;
int ldr3 = 0;
int ldr2 = 0;
int posH = 0;
int posV = 30;
int posHmin = 0;
int posHmax = 180;
int posVmin = 5;
int posVmax = 130;
unsigned long previousMillis = 0;
unsigned long interval = 1000;
const int chipSelect = 10;
float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float energy = 0;
float suhu = 0;
//File TimeFile;
//File SuhuFile;
//File VoltFile;
//File CurFile;
Servo servoH;
Servo servoV;
SoftwareSerial esp(6, 7);// RX, TX

String data;

String server = "aw-abg-indonesia.com"; // www.example.com

String uri = "/jimmy_move.php";// our example is /esppost.php


void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  esp.begin(115200);
  //SD.begin(chipSelect);
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  ina219.begin();
   pinMode(A7, INPUT);
  pinMode(A6, INPUT);
  pinMode(A3, INPUT);
  pinMode(A2, INPUT);
  pinMode(A0, INPUT);
  servoH.attach(9);
  servoV.attach(8);
  servoH.write(posHmin);
  delay(3000);
  servoV.write(posVmin);
  delay(3000);
  Serial.begin(115200);
delay(3000);
Serial.println("stat");
delay(15000);
csq();
 delay(3000);
}

void loop() {
  if(matahari==0){
    gerak();
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    ina219values();
    data = "volt=" + String(loadvoltage)+ "&suhu=" + String(suhu)+"ampere="+String(current_mA);// data sent must be under this form //name1=value1&name2=value2.

Serial.println("post");

httppost();
Serial.println("WAITTTTTT");
digitalWrite(13, LOW);
delay(2000);
digitalWrite(13, HIGH);
delay(60000);
      //Serial.print("MILLIS:");
      //Serial.println(currentMillis);
      //Serial.print("SUHU:");
      //Serial.println(suhu);
      //Serial.print("VOLT:");
      //Serial.println(loadvoltage);
      //Serial.print("CUR:");
      //Serial.println(current_mA);

  }
  
}
void csq() {

esp.println("AT+CSQ");
//if(esp.find("OK") ) Serial.println("Module Reset");

while (esp.available()) {

String tmpResp = esp.readString();

Serial.println(tmpResp);

}
}
void gerak()
{
  ldr7 = analogRead(A7);
  Serial.print(ldr7);
  Serial.print("    A7 \n");
  ldr8 = analogRead(A0);
  Serial.print(ldr8);
  Serial.print("    A0 \n"); 
  ldr6 = analogRead(A6);
  Serial.print(ldr6);
  Serial.print("    A6 \n");
  ldr3 = analogRead(A3);
  Serial.print(ldr3);
  Serial.print("    A3 \n");
  ldr2 = analogRead(A2);
  Serial.print(ldr2);
  Serial.print("    A2 \n");
  
  if ((ldr3 - ldr2 <= 20) &&(ldr7 - ldr6 > 20)){
 if (ldr8 - ldr6 > 20) {
    if (posV >= posVmax) {
      posV = posV;
    }
    else {
      posV += 90;
    }


  }
  else {
    posV = posV;
    matahari=1;
  }

  } else{
    matahari=0;
  }
  
  if (ldr3 - ldr2 > 20) {
    
    if (posH >= posHmax) {
      posH = posH;
    }
    else {
      posH += 5;
    }


  }
  else {
    posH = posH;
    posV -= 90;
  }




  if (ldr2 - ldr3 > 20) {
    if (posH <= posHmin) {
      posH = posH;
    }
    else {
      posH -= 5;
      
    }
  }
  else {
    posH = posH;
    posV += 90;
  }
  //----------------------------------------------------------

  if (ldr7 - ldr6 > 20) {
    if (posV >= posVmax) {
      posV = posV;
    }
    else {
      posV += 5;
    }


  }
  else {
    posV = posV;
  }




  if (ldr6 - ldr7 > 20) {
    if (posV <= posVmin) {
      posV = posV;
    }
    else {
      posV -= 5;
    }
  }
  else {
    posV = posV;
  }
  
  servoH.write(posH);
  servoV.write(posV);
  delay(500);
}

void ina219values() {
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  energy = energy + loadvoltage * current_mA / 3600;
    sensors.requestTemperatures();
  suhu = sensors.getTempCByIndex(0);
}

void httppost () {


esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");//start a TCP connection.
Serial.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");//start a TCP connection.
if( esp.find("OK")) {

Serial.println("TCP connection ready");

} delay(5000);

String  postRequest =

"POST " + uri + " HTTP/1.1\r\n" +

"Host: " + server + "\r\n" +

"Content-Length: " + data.length() + "\r\n" +

"Content-Type: application/x-www-form-urlencoded\r\n" +

"Cache-Control: no-cache\r\n" +

"\r\n" + data;

String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.

esp.print(sendCmd);
Serial.print(sendCmd);
esp.println(postRequest.length() );
Serial.println(postRequest.length() );

delay(200);

if(esp.find(">")) { Serial.println("Sending.."); esp.print(postRequest); Serial.print(postRequest);

if( esp.find("SEND OK")) { Serial.println("Packet sent");

while (esp.available()) {

String tmpResp = esp.readString();

Serial.println(tmpResp);

}

// close the connection

esp.println("AT+CIPCLOSE");

}

}}


