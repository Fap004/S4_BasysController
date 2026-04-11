#include <xc.h>
#include <sys/attribs.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "config.h"
#include "i2c.h"
#include "acl.h"

float fGRangeLSB;   // global variable used to pre-compute the value in g corresponding to each count of the raw value

void ACL_Init()
{
    ACL_ConfigurePins();
    I2C_Init(400000);
    ACL_SetRange(0); // +/- 2g
    ACL_SetRegister(ACL_CTRL_REG1, 1);        // Output data rate at 800Hz, no auto wake, no auto scale adjust, no fast read mode
}

void ACL_ConfigurePins()
{
    // Configure ACL signals as digital input.
    tris_ACL_INT2 = 1;
}

unsigned char ACL_SetRegister(unsigned char bAddress, unsigned char bValue)
{
    unsigned char rgVals[2], bResult;
    rgVals[0] = bAddress;       // register address
    rgVals[1] = bValue;         // register value
    
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

unsigned char ACL_GetDeviceID()
{
    return ACL_GetRegister(ACL_DEVICE_ID);
}

unsigned char ACL_SetRange(unsigned char bRange)
{
    unsigned char bResult, bVal;
    bRange &= 3;    // only 2 least significant bits from bRange are used

    
    bVal = ACL_GetRegister(ACL_XYZDATACFG); // get old value of the register
    bVal &= 0xFC;   // mask out the 2 LSBs
    bVal |= bRange; // set the 2 LSBs according to the range value
    bResult = ACL_SetRegister(ACL_XYZDATACFG, bVal);

    // set fGRangeLSB according to the selected range
    unsigned char bValRange = 1<<(bRange + 2);
    fGRangeLSB = ((float)bValRange)/(1<<12);     // the range is divided to the resolution corresponding to number of bits (12)
    return bResult;
}

void ACL_ReadRawValues(unsigned char *rgRawVals)
{
    unsigned char bVal = ACL_OUT_X_MSB;
    
    I2C_Write(ACL_I2C_ADDR, &bVal, 1, 0);
    I2C_Read(ACL_I2C_ADDR, rgRawVals, 6);
}

float ACL_ConvertRawToValueG(unsigned char *rgRawVals)
{
    // Convert the accelerometer value to G's. 
    // With 12 bits measuring over a +/- ng range we can find how to convert by using the equation:
    // Gs = Measurement Value * (G-range/(2^12))

    unsigned short usReading = (((unsigned short)rgRawVals[0]) << 4) + (rgRawVals[1] >> 4);
    // extend sign from bit 12 bits to 16 bits
    if(usReading & (1<<11))
    {
        usReading |= 0xF000;
    }
  // fGRangeLSB is pre-computed in ACL_SetRange
    float fResult = ((float)((short)usReading)) * fGRangeLSB;
    return fResult;
}

void ACL_ReadGValues(float *rgGVals)
{
    unsigned char rgRawVals[6];
    ACL_ReadRawValues(rgRawVals);
    rgGVals[0] = ACL_ConvertRawToValueG(rgRawVals);
    rgGVals[1] = ACL_ConvertRawToValueG(rgRawVals + 2);
    rgGVals[2] = ACL_ConvertRawToValueG(rgRawVals + 4);
}

void ACL_Close()
{
    I2C1CONbits.ON = 0;     //Disable the I2C module 
}

signed char ACL_8bit(short raw12)
{
    int temp;
    
    temp = ((int)raw12 * 10) / 62; 
    temp = -temp;

    if (temp > 127) temp = 127;
    if (temp < -128) temp = -128;

    if (abs(temp) <= 7) {
        temp = 0;
    }

    return (signed char)temp;
}

signed char ACL_GetRawX_8bit()
{
    unsigned char rgRawVals[6];
    ACL_ReadRawValues(rgRawVals);
    unsigned short usReading = (((unsigned short)rgRawVals[0]) << 4) + (rgRawVals[1] >> 4);
    if(usReading & (1 << 11)) usReading |= 0xF000;
    
    return ACL_8bit((short)usReading);
}

signed char ACL_GetRawY_8bit()
{
    unsigned char rgRawVals[6];
    ACL_ReadRawValues(rgRawVals);
    unsigned short usReading = (((unsigned short)rgRawVals[2]) << 4) + (rgRawVals[3] >> 4);
    if(usReading & (1 << 11)) usReading |= 0xF000;
    
    return ACL_8bit((short)usReading);
}