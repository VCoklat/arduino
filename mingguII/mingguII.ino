const int trigPin = 33;
const int echoPin = 25;
// defines variables
long duration;
int distance,jarak;
#define BT_Merah 13
#define BT_Hijau 12
#define BT_Kuning 14

#define SU_Merah 15
#define SU_Hijau 4
#define SU_Kuning 2

int delaylampumerah = 1000;

int delaylampuhijau = 2000;

void setup() {
  pinMode(BT_Hijau, OUTPUT); //hijau
  pinMode(BT_Merah, OUTPUT); //merah
  pinMode(BT_Kuning, OUTPUT); //kuning

  pinMode(SU_Merah, OUTPUT); //hijau
  pinMode(SU_Kuning, OUTPUT); //merah
  pinMode(SU_Hijau, OUTPUT); //kuning
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200); // Starts the serial communication
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

void macet( int jarak_mobil)
{
  if(jarak_mobil<10){
    Serial.print("Macet!!");
    delay(8000);                       // wait for a second
  }
}

void loop(){
  digitalWrite(BT_Merah, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(SU_Hijau, HIGH); //hijau sisi lain
  
  delay(delaylampuhijau);                       // wait for a second
  
  jarak = cek(33,25);
  macet(jarak);
  
  digitalWrite(SU_Hijau, LOW); //hijau sisi lain
  digitalWrite(BT_Merah, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(SU_Kuning, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delaylampumerah);
  
  digitalWrite(BT_Merah, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(SU_Kuning, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(SU_Merah, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(BT_Hijau, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delaylampuhijau);

  digitalWrite(BT_Hijau, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(BT_Kuning, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delaylampumerah);
  digitalWrite(BT_Kuning, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(SU_Merah, LOW);   // turn the LED on (HIGH is the voltage level)
  
}
