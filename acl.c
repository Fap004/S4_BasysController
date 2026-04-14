#include <xc.h>
#include <sys/attribs.h>
#include <stdlib.h>
#include "config.h"
#include "i2c.h"
#include "acl.h"

void ACL_Init()
{
    ACL_ConfigurePins();
    I2C_Init(400000);
    ACL_SetRegister(ACL_XYZDATACFG, 0x00); // +/- 2g
    ACL_SetRegister(ACL_CTRL_REG1, 1);
}

void ACL_ConfigurePins()
{
    tris_ACL_INT2 = 1;
}

unsigned char ACL_SetRegister(unsigned char bAddress, unsigned char bValue)
{
    unsigned char rgVals[2], bResult;
    rgVals[0] = bAddress;
    rgVals[1] = bValue;
    bResult = I2C_Write(ACL_I2C_ADDR, rgVals, 2, 1);
    return bResult;
}

unsigned char ACL_GetRegister(unsigned char bAddress)
{
    unsigned char bResult;
    I2C_Write(ACL_I2C_ADDR, &bAddress, 1, 0);
    I2C_Read(ACL_I2C_ADDR, &bResult, 1);
    return bResult;
}

void ACL_ReadRawValues(unsigned char *rgRawVals)
{
    unsigned char bVal = ACL_OUT_X_MSB;
    I2C_Write(ACL_I2C_ADDR, &bVal, 1, 0);
    I2C_Read(ACL_I2C_ADDR, rgRawVals, 6);
}

signed char ACL_8bit(short raw12)
{
    int temp;
    temp = ((int)raw12 * 10) / 62;
    temp = -temp;
    if (temp > 127)  temp = 127;
    if (temp < -128) temp = -128;
    if (abs(temp) <= 7) temp = 0;
    return (signed char)temp;
}

signed char ACL_GetRawY()
{
    unsigned char rgRawVals[6];
    ACL_ReadRawValues(rgRawVals);
    unsigned short usReading = (((unsigned short)rgRawVals[2]) << 4) + (rgRawVals[3] >> 4);
    if(usReading & (1 << 11)) usReading |= 0xF000;
    return ACL_8bit((short)usReading);
}