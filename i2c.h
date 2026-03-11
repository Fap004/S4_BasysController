/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    i2c.h

 **/
/* ************************************************************************** */

#ifndef _I2C_H  
#define _I2C_H

#ifdef __cplusplus
extern "C" {
#endif
    
    void I2C_Init();
    unsigned char I2C_Write(unsigned char slaveAddress,
                        unsigned char* dataBuffer,
                        unsigned char bytesNumber,
                        unsigned char stopBit); 
    unsigned char I2C_Read(unsigned char slaveAddress,
                    unsigned char* dataBuffer,
                    unsigned char bytesNumber);
    void I2C_Close();
    
#ifdef __cplusplus
}
#endif

#endif 