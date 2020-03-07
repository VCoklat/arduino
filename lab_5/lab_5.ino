//mosquitto_sub -h soldier.cloudmqtt.com -u ejhukcjd -P NH6L8hwb7Pw3 -p 13209 -t INIX -d
#include <PubSubClient.h>
#include <WiFi.h>
#include "DHTesp.h"
int nilai_acak;
int Builtin =2;
char str_value[8];
int dhtPin = 2; 
DHTesp dht;
//randomseed(micros);
const char* ssid     = "DIGI-X_LOUNGE";
const char* password = "IT Certified";

WiFiClient espClient;
PubSubClient client(espClient);

//char* topic = "esp8266_arduino_out";
const char* server = "soldier.cloudmqtt.com";
const int port = 13209;
const char* user = "ejhukcjd";
const char* pass = "NH6L8hwb7Pw3";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(Builtin, OUTPUT);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  connectMqtt();
  dht.setup(dhtPin, DHTesp::DHT11);
}

void connectMqtt(){
  client.setServer(server,port);
  client.setCallback(receiveMessage);
  while(!client.connected()){
    Serial.println("Mencoba koneksi");
    if(client.connect("ESP32Client",user,pass)){
      Serial.println("tersambung");
    client.subscribe("INIX");
    } else {
      Serial.print("Error");
      delay(5000);
    }
  }
}

void receiveMessage(char* topic, byte* payload, unsigned int length ){
  int ntimes;
  ntimes = (int) ((char)payload[0]-'0');
  Serial.println("Data Blink "+ntimes);
  toBlink(ntimes);
}

void toBlink(int n)
{
  if((n<0) || (n>9)) {n=1;}
  for (int i=0;i<n;i++){
    digitalWrite(Builtin, HIGH );
    delay(1000);
    digitalWrite(Builtin, LOW );
    delay(1000);
  }
}

void loop() {
  client.loop();
  if(!client.connected()){
    Serial.println("Disconnected from Broker");
    connectMqtt();
  }
  // put your main code here, to run repeatedly:
  //TempAndHumidity newValues = dht.getTempAndHumidity();
  //nilai_acak =newValues.temperature;
  //  Serial.println(nilai_acak);
  sprintf(str_value,"%04d", nilai_acak);
  
 // client.publish("INIX",str_value);
  delay(3000);
}
