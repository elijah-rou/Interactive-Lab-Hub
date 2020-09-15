/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fade
*/

int led = 11;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 15;    // how many points to fade the LED by
int count = 0;
int countMax = 3;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
}

// blink with a 500ms interval
void blink(int count, int led){
  for(int i = 0; i<count; i++){
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
}
  

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  analogWrite(led, brightness);

  // change the brightness for next time through the loop
  brightness += fadeAmount;

  // blink count number of times on a fade
  if (brightness >= 255){
    count++;
    blink(count, led);
    fadeAmount *= -1;
  }
  else if (brightness <= 0){
    delay(500);
    fadeAmount *= -1;
  }

  if (count == countMax){
    count = 0;
  }
  
 delay(20);
}
