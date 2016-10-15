#ifndef _I2C_H_
#define _I2C_H_

#define I2C_CLOCK               2
#define EEPROM_SLA              0xA0     //I2C Device address
#define EEPROM_WR               0
#define EEPROM_RD               1

#define PAGE_SIZE               32
#define PAGE_NUMBER             4

void Init_I2C(void);
void One_Page_Read(UINT8 u8PageNumber, UINT8 u8DAT);
void One_Page_Write(UINT8 u8PageNumber, UINT8 u8DAT);

#endif
