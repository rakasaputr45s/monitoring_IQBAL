/*
 *  Created Muhammad Raka Saputra
 */

#define soil 34          // ESP32 pin GIOP34 (ADC0) that connects to AOUT pin of moisture sensor
#define threshold 1000       // CHANGE YOUR THRESHOLD HERE

#define water_level 36                        // pin 34

void setup() {
  Serial.begin(9600);
}

void loop() 
{
  int soil_value                = analogRead(soil); // read the analog value from sensor
  unsigned int sensorValue = analogRead(water_level);

  if (soil_value < threshold) Serial.print("The soil is DRY (");
  else                        Serial.print("The soil is WET (");
  Serial.print(soil_value);
  Serial.println(")");
  Serial.println("Nilai Sensor" + String(water_level));
  delay(500);
}