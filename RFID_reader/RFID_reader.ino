/*
   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <SPI.h>
#include <MFRC522.h>
#include <SD.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define CS_SD 4
#define green 7
#define red 6
#define buzz 5

File myFile;

Servo myservo;

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte nuidPICC[4];
String fileName = "";
bool kartuLama = false;

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus

  pinMode(CS_SD, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  digitalWrite(buzz, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);

  myservo.attach(3);

  rfid.PCD_Init(); // Init MFRC522

  Serial.println(F("RFID Ready."));

  Serial.println(F("Init SD."));

  if (!SD.begin(CS_SD)) {
    Serial.println(F("init fail!"));
    while (1);
  }
  Serial.println(F("init done."));
  digitalWrite(CS_SD, HIGH);
  myservo.write(0);
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // deteksi rfid
    readUID();
    if (kartuLama) {
      gagal();
    } else {
      cekFile();
    }
  }
}

void readUID() {
  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  if (rfid.uid.uidByte[0] != nuidPICC[0] ||
      rfid.uid.uidByte[1] != nuidPICC[1] ||
      rfid.uid.uidByte[2] != nuidPICC[2] ||
      rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("new card detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }

    fileName = String(rfid.uid.uidByte[0], HEX) + "" + String(rfid.uid.uidByte[1], HEX) + "" +
               String(rfid.uid.uidByte[2], HEX) + "" + String(rfid.uid.uidByte[3], HEX) + ".txt";
    Serial.println(fileName);
    kartuLama = false;
  } else {
    Serial.println(F("old card."));
    kartuLama = true;
  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();

}

void cekFile() {
  String counter;
  // baca file ada atau tidak
  digitalWrite(CS_SD, LOW);
  delay(100);
  myFile = SD.open(fileName);
  if (myFile) {
    Serial.print(F("Value : "));

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      counter += (char)myFile.read() ;
    }
    // close the file:
    myFile.close();
    
    digitalWrite(CS_SD, HIGH);
    int temp_counter = 0;
    temp_counter = counter.toInt();
    //Serial.println(temp_counter);
    if (temp_counter <= 0) {
      gagal();
    } else {
      temp_counter = temp_counter - 1;
      writeToSd(temp_counter);
    }
  } else {
    gagal();
    Serial.println(F("File Tidak Ada."));
  }
}

void writeToSd(int sisa) {
  // Create or Update file
  Serial.print(F("file : "));
  Serial.println(fileName);

  digitalWrite(CS_SD, LOW);
  SD.remove(fileName);
  myFile = SD.open(fileName, FILE_WRITE);

  if (myFile) {
    Serial.print(F("Write to file."));
    Serial.println(sisa);
    myFile.println(String(sisa));
    // close the file:
    myFile.close();
    Serial.println(F("done."));
    berhasil();
    doorOpen();
  } else {
    error();
    Serial.println(F("error open file"));
  }

  digitalWrite(CS_SD, HIGH);
}

void gagal () {
  digitalWrite(red, HIGH);
  for (int i = 0; i < 5; i++) {
    digitalWrite(buzz, HIGH);
    delay(50);
    digitalWrite(buzz, LOW);
    delay(50);
  }
  delay(3000);
  digitalWrite(red, LOW);
}

void berhasil() {
  digitalWrite(green, HIGH);
  digitalWrite(buzz, HIGH);
  delay(1000);
  digitalWrite(buzz, LOW);
}

void error(){
  for(int i=0; i<3; i++){
  digitalWrite(red, HIGH);
  digitalWrite(buzz, HIGH);
  delay(500);
  digitalWrite(buzz, LOW);
  digitalWrite(red, LOW);
  delay(500);
  digitalWrite(green, HIGH);
  digitalWrite(buzz, HIGH);
  delay(500);
  digitalWrite(buzz, LOW);
  digitalWrite(green, LOW);
  }
}

void doorOpen() {
  myservo.write(90);
  delay(3000);
  myservo.write(0);
  digitalWrite(green, LOW);
}
