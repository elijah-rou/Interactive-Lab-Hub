
# Motors, Power, Paper Prototyping

## Part B. Actuating Servo motors

### Part 1. Connect the Servo to your breadboard

**a. Which color wires correspond to power, ground and signal?**

Power - *Red*
Ground - *Black*
Signal - *White*

### Part 2. Connect the Servo to your Arduino

**a. Which Arduino pin should the signal line of the servo be attached to?**

Pin 9.

**b. What aspects of the Servo code control angle or speed?**

Angle is controlled by pos, speed can be controlled by either decreasing delay or increasing increment size in the loop! (I used delay)

```python
/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= 100; pos += 1) { // goes from 0 degrees to 100 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(60);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 100; pos >= 0; pos -= 1) { // goes from 100 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(60);                       // waits 15ms for the servo to reach the position
  }
}
```

## Part C. Integrating input and output

```python
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

```

## Part D. Autonomy!
See media/part_d.mov!

## Part E. Paper display + Part F. Make it your own
Due to my move, I had to combine E & F into a single design! The servo arm will measure how boxy this box is, according to how the rotary is set.

See media/part_f.mov!
