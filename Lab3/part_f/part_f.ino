#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// initialize the library with the numbers of the interface pins
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Servo servo;
int encoderA = 6;
int encoderB = 7;

int servoPin = 5;
int servoPos = 0;

/* returns change in encoder state (-1,0,1) */
int read_encoder(){
    static int enc_states[] = {
        0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0  };
    static byte ABab = 0;
    ABab *= 4;                   //shift the old values over 2 bits
    ABab = ABab%16;      //keeps only bits 0-3
    ABab += 2*digitalRead(encoderA)+digitalRead(encoderB); //adds enc_a and enc_b values to bits 1 and 0
    return (enc_states[ABab]);
}

void setup() {
    Serial.begin(115200);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
        for(;;); // Don't proceed, loop forever
    }
    else{
        Serial.println("OLED initialized");
    }
    delay(2000);
    // Set Servo
    servo.attach(5);
    servo.write(0);

    // Set Rotary
    pinMode(encoderA, INPUT_PULLUP);
    pinMode(encoderB, INPUT_PULLUP);

    // Set Display
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,10); 
    display.println("A Box!");
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setCursor(0,10); 
    display.print("Value: 0");
    display.display();
    
}

void loop() {
    static unsigned int counter4x = 0;      //the SparkFun encoders jump by 4 states from detent to detent
    static unsigned int counter = 0;
    static unsigned int prevCounter = 0;
    int data;
    data = read_encoder();
    if(data){
        counter4x += data;
        counter = counter4x/4;
        if (prevCounter != counter){
            display.clearDisplay();
            display.setCursor(0,10); 
            display.print("Value: ");
            display.println(counter);
            display.display();
        }
        prevCounter = counter;
    }
    if(counter > 1700){
        counter = 0;
    }
    else if(counter > 160){
        counter=160;
    }
    else{
        servo.write(counter);
    }
    
}
