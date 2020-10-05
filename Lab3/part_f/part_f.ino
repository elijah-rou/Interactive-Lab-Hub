#include <Servo.h>

// Components
Servo servo;
const int piezo = A0;
const int switchPin = 2;
const int yellow = 3;
const int green = 4;
const int red = 5;

// Knock thresholds
const int quietKnock = 20;
const int loudKnock = 200;

// Variables to store state
int knockValue;
int switchValue;
boolean locked = false;
int numberOfKnocks = 0;

void setup(void){
    // Setup Pins for components
    servo.attach(9);
    pinMode(switchPin, INPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(red, OUTPUT);

    Serial.begin(9600);

    // Light green led and set servo to 0
    digitalWrite(green, HIGH);
    servo.write(0);

    Serial.println("UNLOCKED");
}

boolean checkForKnock(int piezoReading){
    if(piezoReading > quietKnock && piezoReading < loudKnock){
        digitalWrite(yellow, HIGH);
        delay(100);
        digitalWrite(yellow, LOW);
        Serial.print("Knock read: ");
        Serial.println(piezoReading);
        return true;
    }
    else{
        Serial.print("Bad read: ");
        Serial.println(piezoReading);
        return false;
    }

}

void loop(void){
    // If the box is currently unlocked read the switch
    if(locked == false){
        switchValue = digitalRead(switchPin);

        // If the switch is engaged lock the box
        if(switchValue == HIGH){
            locked = true;
            digitalWrite(green, LOW);
            digitalWrite(red, HIGH);
            servo.write(90);
            Serial.println("LOCKED");
            delay(1000);
        }
    }

    // If locked read the piezo
    if(locked == true){
        knockValue = analogRead(piezo);
        if(numberOfKnocks < 3 && knockValue > 0){
            if(checkForKnock(knockValue) == true){
                numberOfKnocks++;
            }
        }
        //Serial.print(3-numberOfKnocks);
        //Serial.println(" knocks to go");
    }

    // Unlock if the number of knocks is 3
    if(numberOfKnocks >= 3){
        locked = false;
        servo.write(0);
        delay(20);
        digitalWrite(green, HIGH);
        digitalWrite(red, LOW);
        numberOfKnocks = 0;
        Serial.println("UNLOCKED");
    }

}
