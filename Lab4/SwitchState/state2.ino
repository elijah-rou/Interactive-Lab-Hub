void saveData(int sensorPin){
  // Save read data to EEPROM
  Serial.println("Writing to EEPROM");
  //int endAddr = min(sizeof(int), EEPROMSIZE);
  for(int i=0; i<EEPROMSIZE; i++){
    //Serial.print("Write at address: ");
    //Serial.println(i);
    int sensorValue = analogRead(sensorPin);
    EEPROM.put(i, sensorValue);
  }
  Serial.println("Data committed to EEPROM!");
}

void doState2(int sensorPin) {
  // Check last state and save data
  digitalWrite(ledPin, LOW);
  if (lastState != 2) {
    saveData(sensorPin);
  }
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}
