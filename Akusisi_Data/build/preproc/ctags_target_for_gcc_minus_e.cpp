# 1 "D:\\Monitoring Iqbal\\Akusisi_Data\\Akusisi_Data.ino"
/*

 *  Created Muhammad Raka Saputra

 */




void setup() {
  Serial.begin(9600);
}

void loop()
{
  int soil_value = analogRead(34 /* ESP32 pin GIOP34 (ADC0) that connects to AOUT pin of moisture sensor*/); // read the analog value from sensor
  unsigned int sensorValue = analogRead(36 /* pin 34*/);

  if (soil_value < 1000 /* CHANGE YOUR THRESHOLD HERE*/) Serial.print("The soil is DRY (");
  else Serial.print("The soil is WET (");
  Serial.print(soil_value);
  Serial.println(")");
  Serial.println("Nilai Sensor" + String(36 /* pin 34*/));
  delay(500);
}
