
#include "Arduino.h"
#include "LoRa_E32.h"

LoRa_E32 e32ttl100(&Serial1, 18, 21, 19); //  RX AUX M0 M1


void setup() {
Serial.begin(9600);
delay(500);
Serial.println("SHUT UP LORa");
// Startup all pins and UART
e32ttl100.begin();
}
void loop() 
{
ResponseStatus rs = e32ttl100.sendMessage("HALLO_DEC");
// Check If there is some problem of succesfully send
Serial.println(rs.getResponseDescription());
}