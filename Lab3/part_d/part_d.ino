#include <Servo.h>

Servo myservo;
int servoPin = 9;
int servoPos = 0;
int potPin = A0;
int potVal = 0;

void setup() {
  myservo.attach(9); 
  pinMode(potPin, INPUT);
}

void loop() {
  for (servoPos = 0; servoPos <= 150; servoPos += 1) {
    potVal = round(analogRead(potPin)/100);
    // in steps of 1 degree
    myservo.write(servoPos);
    delay(potVal);
  }
  for (servoPos = 150; servoPos >= 0; servoPos -= 1) {
    potVal = round(analogRead(potPin)/100);
    myservo.write(servoPos);
    delay(potVal);
  }
}
