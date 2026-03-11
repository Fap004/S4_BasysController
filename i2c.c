/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    i2c.c

 **/
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "i2c.h"

#define I2C_WAIT_TIMEOUT 0x0FFF

void I2C_Init()
{
    I2C1CON = 0;            
    I2C1BRG = 58;
    I2C1CONbits.ON = 1;     
                            
    I2C1CONbits.ACKEN = 1;
}

unsigned char I2C_Write(unsigned char slaveAddress, unsigned char* dataBuffer, unsigned char bytesNumber, unsigned char stopBit)
{
    unsigned char status = 0;
    unsigned char acknowledge = 0;
    unsigned char byte = 0;
    int cnt_timeout;
    I2C1CONbits.SEN = 1;            
    cnt_timeout = 0;
    while(I2C1CONbits.SEN && (++cnt_timeout < I2C_WAIT_TIMEOUT));  
    if(cnt_timeout >= I2C_WAIT_TIMEOUT)
    {
        return 0xFE;    
    }            
    I2C1TRN = slaveAddress << 1;   
    cnt_timeout = 0;
    while(I2C1STATbits.TRSTAT && (++cnt_timeout < I2C_WAIT_TIMEOUT));  
    if(cnt_timeout >= I2C_WAIT_TIMEOUT)
    {
        return 0xFE;    
    }
    acknowledge = I2C1STATbits.ACKSTAT;
    if(acknowledge == 0)         
    {
        for(byte = 0; byte < bytesNumber; byte++)
        {
            I2C1TRN = dataBuffer[byte];
            cnt_timeout = 0;
            while(I2C1STATbits.TRSTAT && (++cnt_timeout < I2C_WAIT_TIMEOUT));  
            if(cnt_timeout >= I2C_WAIT_TIMEOUT)
            {
                return 0xFE;    
            }        
        }
    }
    else
    {
        status = 0xFF;
    }
    if(stopBit)
    {
        I2C1CONbits.PEN = 1;            
        cnt_timeout = 0;
        while(I2C1CONbits.PEN && (++cnt_timeout < I2C_WAIT_TIMEOUT));         
        if(cnt_timeout >= I2C_WAIT_TIMEOUT)
        {
            return 0xFE;    
        }
    }
    return status;
}

unsigned char I2C_Read(unsigned char slaveAddress,
                    unsigned char* dataBuffer,
                    unsigned char bytesNumber)
{
    unsigned char status = 0;
    unsigned char acknowledge = 0;
    unsigned char byte = 0;
    int cnt_timeout;
    I2C1CONbits.RSEN = 1;           
    cnt_timeout = 0;
    while(I2C1CONbits.RSEN && (++cnt_timeout < I2C_WAIT_TIMEOUT));         
    if(cnt_timeout >= I2C_WAIT_TIMEOUT)
    {
        return 0xFE;    
    }
    I2C1TRN = (slaveAddress << 1) + 1;
    cnt_timeout = 0;
    while(I2C1STATbits.TRSTAT && (++cnt_timeout < I2C_WAIT_TIMEOUT));     
    if(cnt_timeout >= I2C_WAIT_TIMEOUT)
    {
        return 0xFE;    
    }
    acknowledge = I2C1STATbits.ACKSTAT;
    if(acknowledge == 0)           
    {
        for(byte = 0; byte < bytesNumber; byte++)
        {
           I2C1CONbits.RCEN = 1;      
            if(byte == (bytesNumber - 1))
            {
                I2C1CONbits.ACKDT = 1;
            }
            else
            {
                I2C1CONbits.ACKDT = 0;
            }
            cnt_timeout = 0;
            while(I2C1CONbits.RCEN && (++cnt_timeout < I2C_WAIT_TIMEOUT));   
            if(cnt_timeout >= I2C_WAIT_TIMEOUT)
            {
                return 0xFE;    
            }
            dataBuffer[byte] = I2C1RCV;
            I2C1CONbits.ACKEN = 1;
            cnt_timeout = 0;
            while(I2C1CONbits.ACKEN && (++cnt_timeout < I2C_WAIT_TIMEOUT));
            if(cnt_timeout >= I2C_WAIT_TIMEOUT)
            {
                return 0xFE;   
            }
        }
    }
    else
    {
        status = 0xFF;
    }
    I2C1CONbits.ACKEN = 1;          
    I2C1CONbits.PEN = 1;            
    cnt_timeout = 0;
    while(I2C1CONbits.PEN && (++cnt_timeout < I2C_WAIT_TIMEOUT));        
    if(cnt_timeout >= I2C_WAIT_TIMEOUT)
    {
        return 0xFE;    
    }
    return status;
}

void I2C_Close()
{
    I2C1CONbits.ON = 0;     
}