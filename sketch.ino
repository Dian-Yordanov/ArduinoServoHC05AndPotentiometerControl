#include <Servo.h>
Servo myservo;  // creates servo object to control a servo

int ps1=9; //servo is connected to digital pin 9
int ps2=10; //servo is connected to digital pin 9
int potPin = A0; // potentiometer is connected to analog 0 pin
int pos = 0; 
int angle = 0;   // variable to store the servo position
int val;    // variable to read the value from the analog pin

void setup() {
  Serial.begin(9600);
  myservo.attach(ps1);
}

void loop() {
  if (Serial.available() && Serial.parseInt() !=0) { // if there is data comming
    delay(50);
    angle = Serial.parseInt();
    if (angle >= 0 && angle <= 180) {
      myservo.write(angle); // rotate servo
      delay(15);
    } 
  }
  else{
    angle = analogRead(potPin); // read the value from the potentiometer and save to angle variable
    angle = map(angle, 0, 1023, 10, 170); // convert potentiometer reading to servo angle
    myservo.write(angle); // rotate servo
    delay(15);
  }
}