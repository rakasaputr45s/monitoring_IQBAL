# 1 "D:\\Monitoring Iqbal\\Soil_Moisture\\Soil_Moisture.ino"
/*

 * This ESP32 code is created by esp32io.com

 *

 * This ESP32 code is released in the public domain

 *

 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-soil-moisture-sensor

 */
# 12 "D:\\Monitoring Iqbal\\Soil_Moisture\\Soil_Moisture.ino"
void setup() {
  Serial.begin(9600);
}

void loop()
{
  int value = analogRead(34 /* ESP32 pin GIOP34 (ADC0) that connects to AOUT pin of moisture sensor*/); // read the analog value from sensor
  if (value < 1000 /* CHANGE YOUR THRESHOLD HERE*/)
    Serial.print("The soil is DRY (");
  else
    Serial.print("The soil is WET (");

  Serial.print(value);
  Serial.println(")");


  delay(500);
}
