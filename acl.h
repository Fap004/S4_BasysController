#ifndef _ACL_H    
#define _ACL_H

#define ACL_I2C_ADDR    0x1D
#define ACL_OUT_X_MSB   0x01 
#define ACL_CTRL_REG1   0x2A
#define ACL_XYZDATACFG  0x0E 

void ACL_Init();
unsigned char ACL_SetRegister(unsigned char bAddress, unsigned char bValue);
unsigned char ACL_GetRegister(unsigned char bAddress);
void ACL_ConfigurePins();
signed char ACL_8bit(short raw12);
signed char ACL_GetRawY();

void I2C_Init(unsigned int clockFreq);
unsigned char I2C_Write(unsigned char slaveAddress,
                        unsigned char* dataBuffer,
                        unsigned char bytesNumber,
                        unsigned char stopBit);
unsigned char I2C_Read(unsigned char slaveAddress,
                       unsigned char* dataBuffer,
                       unsigned char bytesNumber);
#endif