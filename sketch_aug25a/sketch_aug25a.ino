#include "SoftwareSerial.h"
#include <String.h>


unsigned long previousMillis = 0;
String data;

String server = "skripsigeraldo.000webhostapp.com"; // www.example.com
String uri = "/api.php";// our example is /esppost.

String ssid = "FB3NO9"; // ssid
String password = "reynold1"; // password
SoftwareSerial esp(6, 7);// RX, TX

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  esp.begin(9600);
  Serial.begin(9600);
  //reset();
  ////Serial.println(F("INIT"));
  delay(2000);
  connectWifi();
}

void connectWifi() {
    ////Serial.println(F("TRY"));
    String cmd = "AT+CWJAP=\"" + ssid + "\",\"" + password + "\"";
    delay(1000);
    esp.println(cmd);
    if (esp.find("WIFI GOT IP")) {
     // ////Serial.println(F("Connected!"));
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      ////Serial.println(F("Cannot connect to wifi1"));
      delay(5000);
      connectWifi();
    }
}

void loop()
{
  String temp = "";
  if (Serial.available() > 0) {
    temp = Serial.readString();
    //////Serial.println("Suhu=" + temp);
    data = "suhu=" + String(temp);// data sent must be under this form //name1=value1&name2=value2.
    httppost();
    data = "";
  }
}

void httppost () {
  esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");//start a TCP connection.
//  delay(1000);
  if ( esp.find("OK")) {
//    ////Serial.println(F("TCP connection ready"));
  } 
  delay(1000);
  String  postRequest = "POST " + uri + " HTTP/1.1\r\n" +
                        "Host: " + server + "\r\n" +
                        "Content-Length: " + data.length() + "\r\n" +
                        "Content-Type: application/x-www-form-urlencoded\r\n" +
                        "Cache-Control: no-cache\r\n" +
                        "\r\n" + data;
  int bnyk = postRequest.length();
  String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.
  esp.print(sendCmd);
  esp.println(bnyk); //postRequest.length()
//  delay(2000);
  if (esp.find(">")) {
//    ////Serial.println(F("Sending.."));
    esp.print(postRequest);
    while ( esp.available()) {
      String temp = esp.readString();
//      ////Serial.println(temp);
//      if (temp.substring(322,326) == "down") {
//        ////Serial.println("-----------");
//        ////Serial.println(temp.substring(322,327));
//    }
      // temp up
      if (temp.substring(322,326) == "upup"){
         Serial.println("1");
      }
      // temp down
      if (temp.substring(322,326) == "down") {
        Serial.println("2");
      }
      // power
      if (temp.substring(322,326) == "powr") {
        Serial.println("3");      
      }
    }
  }
  // close the connection
//  delay(1000);
  esp.println("AT+CIPCLOSE");
//  delay(1000);
}
