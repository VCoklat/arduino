String jumlah;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello");
  while (!Serial.available()) {
    //Do Absolutely Nothing until something is received over the serial port
  }

  delay(3);  //delay to allow buffer to fill
  if (Serial.available() > 0) {

    jumlah = Serial.readString(); //makes the string readString
  }
  Serial.println(jumlah);
}
