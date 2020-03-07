// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. 

#include <WiFi.h>

// Please input the SSID and password of WiFi
const char* ssid     = "DIGI-X_LOUNGE";
const char* password = "IT Certified";
bool hasWifi;
/*String containing Hostname, Device Id & Device Key in the format:                         */
/*  "HostName=<host_name>;DeviceId=<device_id>;SharedAccessKey=<device_key>"                */
/*  "HostName=<host_name>;DeviceId=<device_id>;SharedAccessSignature=<device_sas_token>"    */

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities
static void InitWifi()
{
  WiFi.disconnect(true);
  Serial.println("Connecting...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  hasWifi = true;
  Serial.print("Connected! IP: ");
  Serial.print(WiFi.localIP());
  Serial.print(" dan Mac Address: ");
  Serial.print(WiFi.macAddress());
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Arduino sketch
void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2,HIGH);
//  Serial.println("ESP32 Device");
//  Serial.println("Initializing...");
//
//  // Initialize the WiFi module
//  Serial.println(" > WiFi");
//  hasWifi = false;
//  InitWifi();
//  if (!hasWifi)
//  {
//    return;
//  }
//  randomSeed(analogRead(0)); 
}

void loop()
{
  
}
