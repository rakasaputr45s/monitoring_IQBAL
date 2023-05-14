#include <Arduino.h>
#line 1 "D:\\EDUTIC\\Soil_Moisture\\Soil_Moisture.ino"
/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-soil-moisture-sensor
 */

#define AOUT_PIN 34          // ESP32 pin GIOP34 (ADC0) that connects to AOUT pin of moisture sensor
#define THRESHOLD 1000       // CHANGE YOUR THRESHOLD HERE

#line 12 "D:\\EDUTIC\\Soil_Moisture\\Soil_Moisture.ino"
void setup();
#line 16 "D:\\EDUTIC\\Soil_Moisture\\Soil_Moisture.ino"
void loop();
#line 12 "D:\\EDUTIC\\Soil_Moisture\\Soil_Moisture.ino"
void setup() {
  Serial.begin(9600);
}

void loop() 
{
  int value = analogRead(AOUT_PIN); // read the analog value from sensor
  if (value < THRESHOLD)
    Serial.print("The soil is DRY (");
  else
    Serial.print("The soil is WET (");

  Serial.print(value);
  Serial.println(")");


  delay(500);
}
