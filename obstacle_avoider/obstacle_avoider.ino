const int trig = 12;
const int echo = 11;
const int leftForward = 2;
const int leftBackward = 3;
const int rightForward = 4;
const int rightBackward = 5;
const int LED = 6;
const int sensorValue = analogRead(A0);
int otomat=0;

void setup() //Setup System
{
    pinMode(trig , OUTPUT);
    pinMode(echo , INPUT);
    pinMode(leftForward , OUTPUT);
    pinMode(leftBackward , OUTPUT);
    pinMode(rightForward , OUTPUT);
    pinMode(rightBackward , OUTPUT);
    pinMode(LED , OUTPUT);
    Serial.begin(9600);
}

void left() //Belok left
{
    digitalWrite(leftForward , HIGH);
    digitalWrite(leftBackward , LOW);
    digitalWrite(rightForward , LOW);
    digitalWrite(rightBackward , HIGH);
}

void right() // Belok right
{
    digitalWrite(leftForward , LOW);
    digitalWrite(leftBackward , HIGH);
    digitalWrite(rightForward , HIGH);
    digitalWrite(rightBackward , LOW);
}

void forward()
{
    digitalWrite(leftForward , HIGH);
    digitalWrite(leftBackward , LOW);
    digitalWrite(rightForward , HIGH);
    digitalWrite(rightBackward , LOW);
}

void backward()
{
    digitalWrite(leftForward , LOW);
    digitalWrite(leftBackward , HIGH);
    digitalWrite(rightForward , LOW);
    digitalWrite(rightBackward , HIGH);
}

void berhenti()
{
    digitalWrite(leftForward , LOW);
    digitalWrite(leftBackward , LOW);
    digitalWrite(rightForward , LOW);
    digitalWrite(rightBackward , LOW);
}

void voltage()
{
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage = sensorValue * (5.0 / 1023.0);
    // print out the value you read:
    Serial.println(voltage);
    if (voltage<9) { digitalWrite(LED , HIGH);} else { digitalWrite(LED , LOW);}
}

void autom()
{
     int duration = 0;
     int distance = 0;
     digitalWrite(trig, LOW);
     delayMicroseconds(2);
     digitalWrite(trig, HIGH);
     delayMicroseconds(10);
     digitalWrite(trig, LOW);
     duration = pulseIn(echo, HIGH);
     distance = duration / 58.2;
     Serial.println(distance);
     if ( distance < 40 || distance > 400 )
     {
        left();
     }
     else
     {
        forward();
     }
}

void loop()
{
    String string= "";
    if(string.length()>0) Serial.println(" ");
    string = "";
    char command;
    if (Serial.available() > 0)
    {
      while(Serial.available() > 0)
      {
        command = ((byte)Serial.read());
        string += command;
        delay(10);
      } 
      Serial.println(string);
    }

   if (otomat==1) autom();
   if (string=="auto") otomat=1;     
  
   if(string == "forward")  {
      forward();
      otomat =0;
   }
   
   if(string == "left")  {
      right();
      otomat =0;
   }
   
   if(string == "right")  {
      for(int i=0; i<100;i++){
      left();
      otomat =0;}
   }
   
   if(string == "stop")  {
      berhenti();
      otomat =0;   
   }
   
   if(string == "backward")  {
      backward();
      otomat =0;
   }
}
