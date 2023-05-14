#include <Arduino.h>
#line 1 "D:\\EDUTIC\\Water_Level\\Water_Level.ino"
// Arduino water level sensor code

// Sensor pins pin D6 LED output, pin A0 analog Input

#define sensorPin 36

#line 7 "D:\\EDUTIC\\Water_Level\\Water_Level.ino"
void setup();
#line 12 "D:\\EDUTIC\\Water_Level\\Water_Level.ino"
void loop();
#line 7 "D:\\EDUTIC\\Water_Level\\Water_Level.ino"
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  unsigned int sensorValue = analogRead(sensorPin);
  Serial.println("Nilai Sensor" + String(sensorValue));
}

