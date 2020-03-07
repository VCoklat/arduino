// Load Wi-Fi library
#include <WiFi.h>
#include "DHTesp.h"
const int trigPin = 33;
const int echoPin = 25;
long duration;
int distance,jarak;
String kalimat;
// Replace with your network credentials
const char* ssid     = "DIGI-X_LOUNGE";
const char* password = "IT Certified";
DHTesp dht;
int dhtPin = 23; 

// Set web server port number to 80
WiFiServer server(8080);
bool blinkin,led;
// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
//String LED_BUILTINState = "off";
//String output27State = "off";

// Assign output variables to GPIO pins
const int LED_BUILTIN = 2;
//const int output27 = 27;
int nilai;
void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(LED_BUILTIN, OUTPUT);
//  pinMode(output27, OUTPUT);
  // Set outputs to LOW
  digitalWrite(LED_BUILTIN, LOW);
//  digitalWrite(output27, LOW);1
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  dht.setup(dhtPin, DHTesp::DHT11);
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
  server.begin();
}

int cek(int trigPin, int echoPin) {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= (duration/2)/29;
  // Prints the distance on the Serial Monitor
//  Serial.print("Durasi: ");
//  Serial.println(duration);
//  Serial.print("Distance: ");
  
  Serial.print("Jarak: ");
  Serial.println(distance);
  return (distance);
  
}

void loop(){
  
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /on") >= 0) {
              //digitalWrite(LED_BUILTIN, HIGH);
              blinkin=false;
              led=true;
            } else if (header.indexOf("GET /blink") >= 0) {
              blinkin=true;
              led=false;
            } else if (header.indexOf("GET /off") >= 0) {
              //Serial.println("GPIO 27 on");
              //output27State = "on";
              //digitalWrite(LED_BUILTIN, LOW);
              blinkin=false;
              led=false;
            } else if (header.indexOf("GET /refresh") >= 0) {
              //Serial.println("GPIO 27 on");
              //output27State = "on";
              //digitalWrite(LED_BUILTIN, LOW);
              nilai=cek(33,25);
              TempAndHumidity newValues = dht.getTempAndHumidity();
              kalimat =(String(newValues.humidity)+"\t" +"\t" + String(newValues.temperature)+"\t" +"\t" + String(newValues.temperature*9/5+32));
  
              //led=false;
            } 
//            else if (header.indexOf("GET /27/off") >= 0) {
//              Serial.println("GPIO 27 off");
//              output27State = "off";
//              digitalWrite(output27, LOW);
//            }
            
            // Display the HTML web page
//            client.println("<!DOCTYPE html><html>");
//            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
//            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
//            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
//            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
//            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
//            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
//            client.println("<body><h1>ESP32 Web Server</h1>");
//            
//            // Display current state, and ON/OFF buttons for GPIO 26  
//            client.println("<p>GPIO 26 - State " + LED_BUILTINState + "</p>");
            // If the LED_BUILTINState is off, it displays the ON button       
//            if (LED_BUILTINState=="off") {
//              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
//            } else {
//              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
//            } 
//            client.println("<p><a href=\"/blink\">LED Blinking</a></p>");
//            client.println("<p><a href=\"/on\">LED ON</a></p>");
//            client.println("<p><a href=\"/off\">LED OFF</a></p>");
           client.print("<html><head><title>Sensor</title>");
           client.print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
           client.print("</head>");
           client.print("<body><h1>Data Sensor</h1>");
           client.printf("<p>Nilai Data Dari Ultrasonic adalah : %d </p>",nilai);
           if (nilai>30) {
              client.println("<p>Kondisi jalanan adalah adalah : lancar </p>");
           } else {
              client.println("<p>Kondisi jalanan adalah adalah : macet </p>");
           }
           client.println(kalimat);
           
           client.print("<p><form action='/refresh'><input type='submit' value='Refresh'></p>");
//            
            // Display current state, and ON/OFF buttons for GPIO 27  
//            client.println("<p>GPIO 27 - State " + output27State + "</p>");
//            // If the output27State is off, it displays the ON button       
//            if (output27State=="off") {
//              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
//            } else {
//              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
//            }
//            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  if(blinkin || led){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }
  if(blinkin || ! led){
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}
