#include "pitches.h"
#include "LiquidCrystal.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int potPin = A0; // Analog pin used
int potVal = 0; // Reading on analog pin
int currentVal = 0; // State of analog pin
int buttonPin = 2; // Pin for button

int minorPentatonicEb[7][2] = {
    {NOTE_DS2, 4},
    {NOTE_FS2, 4},
    {NOTE_GS2, 4},
    {NOTE_AS2, 4},
    {NOTE_CS3, 4},
    {NOTE_DS3, 4},
    {0, 4}
};

int alarm[6][2] = {
    {NOTE_DS1, 2},
    {NOTE_DS1, 2},
    {NOTE_DS1, 2},
    {NOTE_DS1, 2},
    {NOTE_DS1, 2},
    {NOTE_DS1, 2}
};

int startTimerSound[1][2] = {
    {NOTE_DS4, 4}
};

enum State {
    SELECT_TIME,
    COUNTDOWN
};

State currentState = SELECT_TIME;

void play(int melody[][2], int pin, int pauseBetweenNotes) {

    int song_len = sizeof(&melody) / sizeof(&melody[0]);
    for (int i = 0; i < 6; i++) {
        int note = melody[i][0];
        int noteLength = 1000 / melody[i][1];
        tone(pin, note, noteLength);
        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        delay(noteLength * pauseBetweenNotes);
        // stop the tone playing:
        noTone(pin);
    }
}

void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    lcd.clear();

    pinMode(potPin, INPUT);
    // iterate over the notes of the melody:
    lcd.print("I'M A TIMER LOL");
    play(minorPentatonicEb, 4, 1.3);
    lcd.clear();
    lcd.setCursor(0, 0); // Sets the cursor to col 0 and row 0
    lcd.print("Select countdown"); // Prints Sensor Val: to LCD
}

void selectTime() {
    // Control to delay reading of analog input and to only rewrite the screen on a change
    int buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH){
        currentState = COUNTDOWN;
    }
    potVal = round(analogRead(potPin)/100);
    if (potVal != currentVal) {
        lcd.clear();
        lcd.setCursor(0, 0); // Sets the cursor to col 0 and row 0
        lcd.print("Select countdown"); // Prints Sensor Val: to LCD
        lcd.setCursor(0, 1);
        lcd.print(potVal); // Prints value on Potpin to LCD
        currentVal = potVal;
        delay(100);
    }
  
}

void countdown() {
    float counter = currentVal;
    lcd.clear();
    lcd.setCursor(0, 0); // Sets the cursor to col 0 and row 0
    lcd.print("Counting..."); // Prints Sensor Val: to LCD
    //play(startTimerSound, 4, 1.3);
    lcd.setCursor(0, 1);
    while(counter>0){
        lcd.clear();
        lcd.setCursor(0, 0); // Sets the cursor to col 0 and row 0
        lcd.print("Counting..."); // Prints Sensor Val: to LCD
        lcd.setCursor(0, 1);
        lcd.print(round(counter)); // Prints Sensor Val: to LCD
        float beginTime = millis() / 1000;
        delay(1000);
        float endTime = millis() / 1000;
        counter -= (endTime - beginTime);
    }

    lcd.clear();
    lcd.setCursor(0, 0); // Sets the cursor to col 0 and row 0
    lcd.print("TIME UP"); // Prints Sensor Val: to LCD
    play(alarm, 4, 1.8);
    delay(1500);
    setup();
    currentState = SELECT_TIME;
}

void loop() {
    switch (currentState) {
        case SELECT_TIME:
        selectTime();
        break;
        case COUNTDOWN:
        countdown();
        break;
    }
    delay(1);
}
