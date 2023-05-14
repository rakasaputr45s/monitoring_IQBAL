# 1 "D:\\EDUTIC\\Water_Level\\Water_Level.ino"
// Arduino water level sensor code

// Sensor pins pin D6 LED output, pin A0 analog Input



void setup()
{
  Serial.begin(9600);
}

void loop()
{
  unsigned int sensorValue = analogRead(36);
  Serial.println("Nilai Sensor" + String(sensorValue));
}
