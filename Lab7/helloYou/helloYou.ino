int redLed = 6;
int greenLed = 5;
int blueLed = 3;
char inChar;  // character we will use for messages from the RPi

int button = 11;
int buttonState;

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}

void setColor(int red, int green, int blue){
    analogWrite(redLed, 255-red);
    analogWrite(greenLed, 255-green);
    analogWrite(blueLed, 255-blue);  
}

void loop() {
  // read the character we recieve on the serial port from the RPi
  if(Serial.available()) {
    inChar = (char)Serial.read();
  }

  // if we get a 'H', turn the LED on, else turn it off
  if(inChar == 'R'){
    setColor(255, 0, 0);
  }
  
  else if(inChar == 'B'){
    setColor(0, 0, 255);
  }
  else if(inChar == 'G'){
    setColor(0, 255, 0);
  }
  
  else if (inChar == 'L'){
    setColor(0, 0, 0);
  }

  // Button event checker - if pressed, send message to RPi
  int newState = digitalRead(button);
  if (buttonState != newState) {
    buttonState = newState;
    if(buttonState == HIGH){
      Serial.println("light");
    }
    else{
      Serial.println("dark");
    }
  }
}
