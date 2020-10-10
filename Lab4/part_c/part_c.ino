#define VAR_RES A0
#define RED 5
#define GREEN 3
#define BLUE 2

void setup(){
    Serial.begin(9600);
    pinMode(VAR_RES, INPUT);
}


void setColor(int red, int green, int blue){
    analogWrite(RED, 255-red);
    analogWrite(GREEN, 255-green);
    analogWrite(BLUE, 255-blue);  
}

void loop(){
    int res_value = analogRead(VAR_RES);
    Serial.print("Res: ");
    Serial.println(res_value);
    Serial.print("Res%256: ");
    Serial.println(res_value%256);
    Serial.print("255-Res%256: ");
    Serial.println(255-res_value%256);
    Serial.println();
    if(res_value <= 255){
        setColor(0, 0, 0);
    }
    else if(res_value < 511){
        setColor(0, res_value%256, 255-res_value%256);
    }
    else if(res_value < 767){
        setColor(res_value%256, 255-res_value%256, 0);
    }
    else if(res_value < 1023){
        setColor(255-res_value%256, 0, res_value%256);
    }
    // delay(1000);
}