// Arduino water level sensor code

// Sensor pins pin D6 LED output, pin A0 analog Input

#define sensorPin 34                        // pin 34

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  unsigned int sensorValue = analogRead(sensorPin);
  Serial.println("Nilai Sensor" + String(sensorValue));
}
