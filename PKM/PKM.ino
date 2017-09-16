#define echoPin1 2 // Echo Pin
#define trigPin1 3 // Trigger Pin
#define echoPin2 4 // Echo Pin
#define trigPin2 5 // Trigger Pin
#define kirimaju 6 // Trigger Pin
#define kirimundur 7 // Trigger Pin
#define kananmaju 8 // Trigger Pin
#define kananmundur 9 // Trigger Pin
#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68

int otomat=0;
long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor = 0;

byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}

void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
void displayTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10)
  {
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch(dayOfWeek){
  case 1:
    Serial.println("Sunday");
    break;
  case 2:
    Serial.println("Monday");
    break;
  case 3:
    Serial.println("Tuesday");
    break;
  case 4:
    Serial.println("Wednesday");
    break;
  case 5:
    Serial.println("Thursday");
    break;
  case 6:
    Serial.println("Friday");
    break;
  case 7:
    Serial.println("Saturday");
    break;
  }
}

void setup()
{
  Wire.begin();
  Serial.begin(9600);
    // DS3231 seconds, minutes, hours, day, date, month, year
  //setDS3231time(0,5,13,7,30,04,16);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(kirimaju, OUTPUT);
  pinMode(kirimundur, OUTPUT);
  pinMode(kananmaju, OUTPUT);
  pinMode(kananmundur, OUTPUT);
}

void loop() {
  //delay(1000); // every second
  char command;
  String string;
  if (otomat==1) autom();
  if (otomat==0) manual();
  if(string.length()>0) Serial.println(" ");
  string = "";
  if (Serial.available() > 0)
  {
    while(Serial.available() > 0)
    {
      command = ((byte)Serial.read());
      string += command;
      delay(10);
    } 
    Serial.println(string);
    if(string =="manual") otomat =0;
    else 
    if(string == "auto")  {
      otomat=1;
    }
    if(string == "maju")  {
      maju1();
      otomat=0;
    }
    else if(string == "kiri")  
    {
      kiri1();
      otomat=0;
    }
    else if(string == "kanan")  {
      kanan1();
      otomat =0;
    }
    else if(string == "mundur")  {
      mundur1();
      otomat=0;
    }
     else if(string == "jam")  {
    displayTime(); // display the real-time clock data on the Serial Monitor,
    }
    if(string.length()>0) 
    {
      Serial.println(" ");
    }
    string = "";
  }  
}

void manual()
{
  digitalWrite(kirimaju, LOW);
  digitalWrite(kirimundur, LOW);
  digitalWrite(kananmaju, LOW);
  digitalWrite(kananmundur, LOW);  
}

void autom()
{
  SonarSensor(trigPin1, echoPin1);
  RightSensor = distance;
  SonarSensor(trigPin2, echoPin2);
  LeftSensor = distance;
  //if (RightSensor > 400) RightSensor = 0;
  //if (LeftSensor > 400) LeftSensor = 0;
  if (RightSensor>20 && LeftSensor>20) maju();
  if (LeftSensor<=20) 
  {
    kanan();
  }
  if (RightSensor<=20) 
  {
    kiri();
  }
  if (RightSensor<20 && LeftSensor<20) 
  {
    mundur();
  }
  /*Serial.print(RightSensor);
  Serial.print("-");
  Serial.println(LeftSensor);*/
}

void SonarSensor(int trigPin,int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
}


void maju()
{
  for (int i=0; i<20000;i++)
  {
  digitalWrite(kirimaju, HIGH);
  digitalWrite(kirimundur, LOW);
  digitalWrite(kananmaju, HIGH);
  digitalWrite(kananmundur, LOW);
  }
}

void kanan()
{
    for (int i=0; i<20000;i++)
  {
    digitalWrite(kirimaju, HIGH);
    digitalWrite(kirimundur, LOW);
    digitalWrite(kananmaju, LOW);
    digitalWrite(kananmundur, HIGH);
  }
}

void kiri()
{
    for (int i=0; i<20000;i++)
  {
    digitalWrite(kananmaju, HIGH);
    digitalWrite(kananmundur, LOW);
    digitalWrite(kirimaju, LOW); 
    digitalWrite(kirimundur, HIGH); 
  }
}
void mundur()
{
    for (int i=0; i<20000;i++)
  {
    digitalWrite(kananmaju, LOW);
    digitalWrite(kananmundur, HIGH);
    digitalWrite(kirimaju, LOW); 
    digitalWrite(kirimundur, HIGH);
  }
}

void maju1()
{
  for (int i=0; i<30000;i++)
  {
  digitalWrite(kirimaju, HIGH);
  digitalWrite(kirimundur, LOW);
  digitalWrite(kananmaju, HIGH);
  digitalWrite(kananmundur, LOW);
  }
}

void kanan1()
{
  for (int i=0; i<30000;i++)
  {
    digitalWrite(kirimaju, HIGH);
    digitalWrite(kirimundur, LOW);
    digitalWrite(kananmaju, LOW);
    digitalWrite(kananmundur, HIGH);
  }
}

void kiri1()
{
    for (int i=0; i<30000;i++)
  {
    digitalWrite(kananmaju, HIGH);
    digitalWrite(kananmundur, LOW);
    digitalWrite(kirimaju, LOW); 
    digitalWrite(kirimundur, HIGH); 
  }
}
void mundur1()
{
  for (int i=0; i<30000;i++)
  {
    digitalWrite(kananmaju, LOW);
    digitalWrite(kananmundur, HIGH);
    digitalWrite(kirimaju, LOW); 
    digitalWrite(kirimundur, HIGH);
  }
}
