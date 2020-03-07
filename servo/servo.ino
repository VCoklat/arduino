/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo,myservo1;  // create servo object to control a servo
// twelve servo objects can be created on most boards

void setup() {
  myservo1.attach(12);  // attaches the servo on pin 9 to the servo object
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object

}

void loop() {
   myservo.write(0);
   myservo1.write(180);
}

