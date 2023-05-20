#include <ModbusMasterPzem017.h>
static uint8_t slaveModul1 = 0x01; //PZem Address
static uint8_t slaveModul2 = 0x02; //PZem Address

static uint16_t NewshuntAddr = 0x0001;      // Declare your external shunt value. Default is 100A, replace to "0x0001" if using 50A shunt, 0x0002 is for 200A, 0x0003 is for 300A
static uint8_t resetCommand = 0x42;         // reset energy command

static char satu = 1;
static char dua  = 2;

ModbusMaster nodeSatu;
ModbusMaster nodeDua;

float PZEMVoltage[2];
float PZEMCurrent[2];
float PZEMPower[2];
float PZEMEnergy[2];

int resetstate;
unsigned long OnTime;
unsigned long OffTime;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N2);
  setShunt(slaveModul1);
  setShunt(slaveModul2);
  nodeSatu.begin(slaveModul1, Serial2);
  nodeDua.begin(slaveModul2, Serial2);

  delay(1000);
}

void loop() {
  unsigned long resetcurrentMillis = millis();

  uint8_t result;
  result = nodeSatu.readInputRegisters(0x0000, 6);
  if (result != nodeSatu.ku8MBSuccess) Serial.println("Failed to read modul 1");
  else  {
    uint32_t tempdouble = 0x00000000;
    PZEMVoltage[satu] = nodeSatu.getResponseBuffer(0x0000) / 100.0;
    PZEMCurrent[satu] = nodeSatu.getResponseBuffer(0x0001) / 100.0;
    tempdouble =  (nodeSatu.getResponseBuffer(0x0003) << 16) + nodeSatu.getResponseBuffer(0x0002); // get the power value. Power value is consists of 2 parts (2 digits of 16 bits in front and 2 digits of 16 bits at the back) and combine them to an unsigned 32bit
    PZEMPower[satu] = tempdouble / 10.0; //Divide the value by 10 to get actual power value (as per manual)
    tempdouble =  (nodeSatu.getResponseBuffer(0x0005) << 16) + nodeSatu.getResponseBuffer(0x0004);  //get the energy value. Energy value is consists of 2 parts (2 digits of 16 bits in front and 2 digits of 16 bits at the back) and combine them to an unsigned 32bit
    PZEMEnergy[satu] = tempdouble;
    Serial.println("MODUL 1");
    Serial.print(PZEMVoltage[satu], 2); //Print Voltage value on Serial Monitor with 1 decimal*/
    Serial.print("V   ");
    Serial.print(PZEMCurrent[satu], 2); Serial.print("A   ");
    Serial.print(PZEMPower[satu], 3); Serial.print("W  ");
    Serial.print(PZEMEnergy[satu], 0); Serial.print("Wh  ");
    Serial.println();
  } 

  delay(500);

    result = nodeDua.readInputRegisters(0x0000, 6);
  if (result != nodeDua.ku8MBSuccess) Serial.println("Failed to read modul 1");
  else  {
    uint32_t tempdouble = 0x00000000;
    PZEMVoltage[dua] = nodeDua.getResponseBuffer(0x0000) / 100.0;
    PZEMCurrent[dua] = nodeDua.getResponseBuffer(0x0001) / 100.0;
    tempdouble =  (nodeDua.getResponseBuffer(0x0003) << 16) + nodeDua.getResponseBuffer(0x0002); //    get the power value. Power value is consists of 2 parts (2 digits of 16 bits in front and 2 digits of 16 bits at the back) and combine them to an unsigned 32bit
    PZEMPower[dua] = tempdouble / 10.0; //Divide the value by 10 to get actual power value (as per manual)
    tempdouble =  (nodeDua.getResponseBuffer(0x0005) << 16) + nodeDua.getResponseBuffer(0x0004);  //   get the energy value. Energy value is consists of 2 parts (2 digits of 16 bits in front and 2 digits of 16 bits at the back) and combine them to an unsigned 32bit
    PZEMEnergy[dua] = tempdouble;
    Serial.println("MODUL 2");
    Serial.print(PZEMVoltage[dua], 2);                                                            //   Print Voltage value on Serial Monitor with 1 decimal*/
    Serial.print("V   ");
    Serial.print(PZEMCurrent[dua], 2); Serial.print("A   ");
    Serial.print(PZEMPower[dua], 3); Serial.print("W  ");
    Serial.print(PZEMEnergy[dua], 0); Serial.print("Wh  ");
    Serial.println();
  } 
  delay(500);
} 



/* hold the reset pin HIGH for 4 seconds and the energy will reset. The onboard LED will blink*/

void energyreset() {
  // if (OnTime >= (OffTime + WaitTime)) { // if the OnTime is >= to the OffTime + WaitTime
  //   static uint8_t resetCommand = 0x42;                                                               /* reset command code*/
  //   static uint8_t slaveAddr = 0x01;

  //   uint16_t u16CRC = 0xFFFF;                                                                         /* declare CRC check 16 bits*/
  //   u16CRC = crc16_update(u16CRC, slaveAddr);
  //   u16CRC = crc16_update(u16CRC, resetCommand);
  //   /* trigger transmission mode*/

  //   Serial2.write(slaveAddr);                                                                         /* send device address in 8 bit*/
  //   Serial2.write(resetCommand);                                                                      /* send reset command */
  //   Serial2.write(lowByte(u16CRC));                                                                   /* send CRC check code low byte  (1st part) */
  //   Serial2.write(highByte(u16CRC));                                                                  /* send CRC check code high byte (2nd part) */
  //   Serial.println("Energy Reset");
  //   delay(300);
  // }
}



void setShunt(uint8_t slaveAddr) {
  static uint8_t SlaveParameter = 0x06;                                                             /* Write command code to PZEM */
  static uint16_t registerAddress = 0x0003;                                                         /* change shunt register address command code */

  uint16_t u16CRC = 0xFFFF;                                                                         /* declare CRC check 16 bits*/
  u16CRC = crc16_update(u16CRC, slaveAddr);                                                         // Calculate the crc16 over the 6bytes to be send
  u16CRC = crc16_update(u16CRC, SlaveParameter);
  u16CRC = crc16_update(u16CRC, highByte(registerAddress));
  u16CRC = crc16_update(u16CRC, lowByte(registerAddress));
  u16CRC = crc16_update(u16CRC, highByte(NewshuntAddr));
  u16CRC = crc16_update(u16CRC, lowByte(NewshuntAddr));

  Serial.println("Change shunt address");
  Serial2.write(slaveAddr); //these whole process code sequence refer to manual
  Serial2.write(SlaveParameter);
  Serial2.write(highByte(registerAddress));
  Serial2.write(lowByte(registerAddress));
  Serial2.write(highByte(NewshuntAddr));
  Serial2.write(lowByte(NewshuntAddr));
  Serial2.write(lowByte(u16CRC));
  Serial2.write(highByte(u16CRC));
  delay(10); delay(100);
  while (Serial2.available()) {
    Serial.print(char(Serial2.read()), HEX); //Prints the response and display on Serial Monitor (Serial)
    Serial.print(" ");
  }
} 
//setShunt Ends
