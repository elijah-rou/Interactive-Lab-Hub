# Data Logger (and using cool sensors!)

## Part A.  Writing to the Serial Monitor
 
**a. Based on the readings from the serial monitor, what is the range of the analog values being read?**
0 to 1023.
**b. How many bits of resolution does the analog to digital converter (ADC) on the Arduino have**
7-bit resolution.
## Part B. RGB LED

## Part C. Resistance & Voltage Varying Sensors 
One of the useful aspects of the Arduino is the multitude of analog input pins. We'll explore this more now.
 
### FSR

**a. What voltage values do you see from your force sensor?**

0 to 1000V.

**b. What kind of relationship does the voltage have as a function of the force applied? (e.g., linear?)**

Exponential (little force to actuate the sensor but substantial force to push it to the outmost range).

**c. In `Examples->Basic->Fading` the RGB LED values range from 0-255. What do you have to do so that you get the full range of output voltages from the RGB LED when using your FSR to change the LED color?**
Cycle through the FSR values mod256 as follows:
```c++
if(fsr_value <= 255){
    setColor(0, 0, 0);
}
else if(fsr_value < 511){
    setColor(0, fsr_value%256, 255-fsr_value%256);
}
else if(fsr_value < 767){
    setColor(fsr_value%256, 255-fsr_value%256, 0);
}
else if(fsr_value < 1023){
    setColor(255-fsr_value%256, 0, fsr_value%256);
}
```

## Flex Sensor, Photo cell, Softpot

**a. What resistance do you need to have in series to get a reasonable range of voltages from each sensor?**

**b. What kind of relationship does the resistance have as a function of stimulus? (e.g., linear?)**

Control the colors of the LED using the above sensors ( including FSR )

## Part D. I2C Sensors 

### Accelerometer
 
**a. Include your accelerometer read-out code in your write-up.**


## Part E. Logging values to the EEPROM and reading them back
 
### 1. Reading and writing values to the Arduino EEPROM

**a. Does it matter what actions are assigned to which state? Why?**

**b. Why is the code here all in the setup() functions and not in the loop() functions?**

**c. How many byte-sized data samples can you store on the Atmega328?**

**d. How would you get analog data from the Arduino analog pins to be byte-sized? How about analog data from the I2C devices?**

**e. Alternately, how would we store the data if it were bigger than a byte? (hint: take a look at the [EEPROMPut](https://www.arduino.cc/en/Reference/EEPROMPut) example)**

### 2. Design your logger
 
**a. Turn in a copy of your final state diagram.**

## Part G. Create your own data logger!
 
**a. Record and upload a short demo video of your logger in action.**
