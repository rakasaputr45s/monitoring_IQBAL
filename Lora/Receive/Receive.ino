
/*
                                                                                                                بِسْمِ اللّٰهِ الرَّحْمٰنِ الرَّحِيْمِ  
                                                                                                                    اَلْحَمْدُ لِلّٰهِ رَبِّ الْعٰلَمِيْ  
                                                                                                                          الرَّحْمٰنِ الرَّحِيْمِ          
                                                                                                                          مٰلِكِ يَوْمِ الدِّيْنِ   
                                                                                                                 اِيَّاكَ نَعْبُدُ وَاِيَّاكَ نَسْتَعِيْنُ
                                                                                                                اِھْدِنَا الصِّرَاطَ الْمُسْتَـقِيْمَ
                                                                                        صِرَاطَ الَّذِيۡنَ اَنۡعَمۡتَ عَلَيۡهِمۡ ۙ غَيۡرِ الۡمَغۡضُوۡبِ عَلَيۡهِمۡ وَلَا الضَّآلِّيۡنَ   

*/

#include "Arduino.h"
#include "LoRa_E32.h"


LoRa_E32 e32ttl100(&Serial2, 18, 21, 19); //  RX AUX M0 M1

void setup() {
Serial.begin(9600);
delay(500);
Serial.print// Startup all pins and UART
e32ttl100.begin();
}
void loop() 
{
if (e32ttl100.available()) 
{
// read the String message
ResponseContainer rc = e32ttl100.receiveMessage();
// Is something goes wrong print error
if (rc.status.code!=1)   rc.status.getResponseDescription();
else                     Serial.println(rc.data);
}
}