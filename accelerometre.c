/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    accelerometre.c

 **/
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>
#include <math.h>
#include "config.h"
#include "accelerometre.h"
#include "i2c.h"

#define RAD_TO_DEG 57.29577951f

float fGRangeLSB; 

void ACL_Init()
{
    I2C_Init();
    ACL_SetRange(0); 
    ACL_SetRegister(ACL_CTRL_REG1, 1);       
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

unsigned char ACL_GetDeviceID()
{
    return ACL_GetRegister(ACL_DEVICE_ID);
}

unsigned char ACL_SetRange(unsigned char bRange)
{
    unsigned char bResult, bVal;
    bRange &= 3;    
    
    bVal = ACL_GetRegister(ACL_XYZDATACFG); 
    bVal &= 0xFC;   
    bVal |= bRange;
    bResult = ACL_SetRegister(ACL_XYZDATACFG, bVal);

    unsigned char bValRange = 1<<(bRange + 2);
    fGRangeLSB = ((float)bValRange)/(1<<12);     
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
    unsigned short usReading = (((unsigned short)rgRawVals[0]) << 4) + (rgRawVals[1] >> 4);

    if(usReading & (1<<11))
    {
        usReading |= 0xF000;
    }
    
    float fResult = ((float)((short)usReading)) * fGRangeLSB;
    return fResult;
}

void ACL_Close()
{
    I2C1CONbits.ON = 0;     
}

float ACL_ReadXOnly() {
    unsigned char reg = ACL_OUT_X_MSB; 
    unsigned char data[2];             
    short rawX;

    I2C_Write(ACL_I2C_ADDR, &reg, 1, 0); 

    I2C_Read(ACL_I2C_ADDR, data, 2);

    rawX = ((short)data[0] << 8) | data[1];
    rawX >>= 4; 

    return (float)rawX / 1024.0f;
}

float calculer_angle_accel() {
    float xVal = ACL_ReadXOnly(); 
    if (xVal > 1.0f) xVal = 1.0f;
    if (xVal < -1.0f) xVal = -1.0f;
    return asin(xVal) * RAD_TO_DEG;
}