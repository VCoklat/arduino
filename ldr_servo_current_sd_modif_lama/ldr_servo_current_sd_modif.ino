 #include <DallasTemperature.h>
#include <OneWire.h>
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_INA219.h>
//#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include "SdFat.h"
SdFat SD;

#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);
Adafruit_INA219 ina219;
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
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
File TimeFile;
File SuhuFile;
File VoltFile;
File CurFile;
Servo servoH;
Servo servoV;

void setup() {
  SD.begin(chipSelect);
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
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    gerak();
    previousMillis = currentMillis;
    ina219values();
  
    TimeFile = SD.open("TIME.txt", FILE_WRITE);
    if (TimeFile) {
      Serial.print("YEAH");
      TimeFile.println(currentMillis);
      TimeFile.close();
    }
    
    SuhuFile = SD.open("SUHU.txt", FILE_WRITE);
    if (SuhuFile) {
      SuhuFile.println(suhu);
      SuhuFile.close();
      
    }

    VoltFile = SD.open("VOLT.txt", FILE_WRITE);
    if (VoltFile) {
      VoltFile.println(loadvoltage);
      VoltFile.close();
    }


    CurFile = SD.open("CUR.txt", FILE_WRITE);
    if (CurFile) {
      CurFile.println(current_mA);
      CurFile.close();
    }

  }
  if(matahari==0){
    gerak();
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
  //    delay(100);
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




