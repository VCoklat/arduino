/*
   --------------------------------------------------------------------------------------------------------------------
   Example sketch/program showing how to read new NUID from a PICC to serial.
   --------------------------------------------------------------------------------------------------------------------
   This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid

   Example sketch/program showing how to the read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
   Reader on the Arduino SPI interface.

   When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
   then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
   you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
   will show the type, and the NUID if a new card has been detected. Note: you may see "Timeout in communication" messages
   when removing the PICC from reading distance too early.

   @license Released into the public domain.

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

#define SS_PIN 10
#define RST_PIN 9
#define CS_SD 4

File myFile;

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

//MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte nuidPICC[4];
String fileName = "";

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  pinMode(CS_SD, OUTPUT);
  rfid.PCD_Init(); // Init MFRC522

  Serial.println(F("RFID Ready."));

  Serial.println(F("SD card init."));

  if (!SD.begin(CS_SD)) {
    Serial.println(F("init fail!"));
    while (1);
  }
  Serial.println(F("init done."));
  digitalWrite(CS_SD, HIGH);
  scanReady();
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // deteksi rfid
    readUID();
    cekFile();
    scanReady();
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
  } 
  
//  else {
//    Serial.println(F("Kartu Lama Terdeteksi."));
//    scanReady();
//  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();

}

void cekFile() {
  // baca file ada atau tidak
  digitalWrite(CS_SD, LOW);
  myFile = SD.open(fileName);
  if (myFile) {
    Serial.print(F("Sudah ada file : "));
    Serial.println(fileName);
    Serial.print(F("Value : "));

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
    digitalWrite(CS_SD, HIGH);
    
    // ada, tanya mau update tidak.
    Serial.println(F("Update value? (y/n)"));
    while (!Serial.available()) {
    //Do Absolutely Nothing until something is received over the serial port
    }

    if (Serial.available() > 0) {
      String temp = Serial.readString();
      Serial.println(temp);
      if (temp.substring(0, 1) == "Y" || temp.substring(0, 1) == "y"){
        Serial.println(F("Update File."));
        writeToSd();
      } else {
        Serial.println(F("Value Tetap!"));
      }
    }
    

    
  } else {
    // if the file didn't open, print an error:
    Serial.println(F("Create File."));
    writeToSd();
  }
}

void writeToSd(){
  // Create or Update file
  String jumlah = "";
  Serial.println(F("Masukkan Jumlah:"));
  while (!Serial.available()) {
    //Do Absolutely Nothing until something is received over the serial port
  }

  delay(3);  //delay to allow buffer to fill
  if (Serial.available() > 0) {

    jumlah = Serial.readString(); //makes the string readString
  }
  Serial.print(F("file : "));
  Serial.println(fileName);


  digitalWrite(CS_SD, LOW);
  SD.remove(fileName);
  myFile = SD.open(fileName, FILE_WRITE);

  if (myFile) {
    Serial.print(F("Writing."));
    myFile.println(jumlah);
    // close the file:
    myFile.close();
    Serial.println(F("done."));
  } else {
    // if the file didn't open, print an error:
    Serial.println(F("error open file"));
  }

  digitalWrite(CS_SD, HIGH);
}

void scanReady(){
  Serial.println(F("---Scan Kartu---"));
}
