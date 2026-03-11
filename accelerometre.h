/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    accelerometre.h

 **/
/* ************************************************************************** */

#ifndef _ACCELEROMETRE_H  
#define _ACCELEROMETRE_H

#define ACL_I2C_ADDR        0x1D
#define ACL_OUT_X_MSB       0x01 
#define ACL_CTRL_REG1       0x2A
#define ACL_DEVICE_ID       0x0D 
#define ACL_XYZDATACFG      0x0E 

#ifdef __cplusplus
extern "C" {
#endif
    
    void ACL_Init();
    void ACL_ReadRawValues(unsigned char *rgRawVals);
    unsigned char ACL_SetRange(unsigned char bRange);
    float ACL_ConvertRawToValueG(unsigned char *rgRawVals);
    unsigned char ACL_SetRegister(unsigned char bAddress, unsigned char bValue);
    unsigned char ACL_GetRegister(unsigned char bAddress);
    float ACL_ReadXOnly();
    float calculer_angle_accel();
    
#ifdef __cplusplus
}
#endif

#endif 