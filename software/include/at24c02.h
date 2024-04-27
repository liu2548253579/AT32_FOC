#ifndef at24c02_h
#define at24c02_h

#include "Arduino.h"
//---------------------------------------------------------------------------------------------------------
class at24c02 {
  public:
    at24c02(uint8_t, TwoWire &w);                             // EEPROM (I2C адрес)
    void write(uint8_t m_addr, uint8_t m_data);   // записва клетка на адрес m_addr с данни m_data
    void update(uint8_t m_addr, uint8_t m_data);  // чете клетка и записва данни само при разлика
    uint8_t read(uint8_t m_addr);                 // чете съдържанието на клетка с адрес m_addr
  private:
    uint8_t m_chip_addr;                          // I2C адрес
    TwoWire *wire_24c02;
};
//---------------------------------------------------------------------------------------------------------
#endif
