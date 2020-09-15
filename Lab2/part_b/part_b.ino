
// https://create.arduino.cc/projecthub/Guitarman1/displaying-sensor-values-on-lcd-c0c44f
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7,8,9,10,11,12);

int potPin = A0; // Analog pin used
int potVal = 0; // Reading on analog pin
int currentVal = 0; // State of analog pin

void setup(){
// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(potPin, INPUT);
}

void loop(){
  // Control to delay reading of analog input and to only rewrite the screen on a change
  potVal = round(analogRead(potPin));
  if(potVal != currentVal){
    lcd.clear();
    lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
    lcd.print("A0: "); // Prints Sensor Val: to LCD
    lcd.print(potVal); // Prints value on Potpin to LCD
    currentVal = potVal;
  }
  delay(200);
}
