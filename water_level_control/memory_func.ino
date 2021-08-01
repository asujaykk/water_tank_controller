#include <EEPROM.h>


//EEPROM ADRESS OF MAJOR PARAMETER values  
    int manual_on_addr=0;
    int motor_on_addr=1;
    int _MTR_OFF_DELAY_addr=2;
    int S_THRESHOLD_addr=4;


void readParametersFromMemory(){
  manual_on = readFromAdress(manual_on_addr);
  //motor_on = readFromAdress(motor_on_addr);
  _MTR_OFF_DELAY = readIntFromEEPROM(_MTR_OFF_DELAY_addr);
  S_THRESHOLD = readIntFromEEPROM(S_THRESHOLD_addr);
}
 
void writeParametersToMemory(){
   writeToAdress(manual_on_addr,char(manual_on));
   //writeToAdress(motor_on_addr,char(motor_on));
   writeIntIntoEEPROM(_MTR_OFF_DELAY_addr,_MTR_OFF_DELAY);
   writeIntIntoEEPROM(S_THRESHOLD_addr,S_THRESHOLD);
}



void writeToAdress(int addr,int val){
  EEPROM.write(addr, val);
}

int readFromAdress(int addr){
  return (EEPROM.read(addr));
}


void writeIntIntoEEPROM(int address, int number)
{ 
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

int readIntFromEEPROM(int address)
{
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}
