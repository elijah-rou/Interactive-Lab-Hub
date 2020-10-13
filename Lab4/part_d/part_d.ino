#include <Adafruit_LIS3DH.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
    // Start Monitor and allocate memory for I2C devices
    Serial.begin(115200);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
        for(;;); // Don't proceed, loop forever
    }
    else{
        Serial.println("OLED initialised");
    }
    Serial.println("LIS3DH test!");

    if (!lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
        Serial.println("LIS3DH allocation failed");
        for(;;);
    }
    Serial.println("Accelerometer initialised");
    delay(2000);

    // Report polling rate for Accelerometer
    Serial.print("Range = "); Serial.print(2 << lis.getRange());
    Serial.println("G");
    Serial.print("Data rate set to: ");
    switch (lis.getDataRate()) {
        case LIS3DH_DATARATE_1_HZ: Serial.println("1 Hz"); break;
        case LIS3DH_DATARATE_10_HZ: Serial.println("10 Hz"); break;
        case LIS3DH_DATARATE_25_HZ: Serial.println("25 Hz"); break;
        case LIS3DH_DATARATE_50_HZ: Serial.println("50 Hz"); break;
        case LIS3DH_DATARATE_100_HZ: Serial.println("100 Hz"); break;
        case LIS3DH_DATARATE_200_HZ: Serial.println("200 Hz"); break;
        case LIS3DH_DATARATE_400_HZ: Serial.println("400 Hz"); break;

        case LIS3DH_DATARATE_POWERDOWN: Serial.println("Powered Down"); break;
        case LIS3DH_DATARATE_LOWPOWER_5KHZ: Serial.println("5 Khz Low Power"); break;
        case LIS3DH_DATARATE_LOWPOWER_1K6HZ: Serial.println("16 Khz Low Power"); break;
    }

     // Set Display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,10); 
    display.println("Accelerometer");
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setCursor(0,10); 
    display.print("X:0 Y:0 Z:0");
    display.display();
}

void loop() {
    // Clear Display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0); 

    // Read Accelerometer
    lis.read();
    auto x = lis.x;
    auto y = lis.y;
    auto z = lis.z;

    // Print to display
    display.print("X:");
    display.print(x);
    display.setCursor(64, 0);
    display.print("Y:");
    display.print(y);
    display.setCursor(0, 16);
    display.print("Z:");
    display.println(z);
    display.display();

    // Print to Monitor
    Serial.print("X:  "); Serial.print(lis.x);
    Serial.print("  \tY:  "); Serial.print(lis.y);
    Serial.print("  \tZ:  "); Serial.print(lis.z);
    Serial.println();
    delay(200);
}