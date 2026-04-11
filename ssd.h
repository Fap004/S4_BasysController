#ifndef _SSD_H    
#define _SSD_H

void SSD_Init();
void SSD_WriteDigits(unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3, \
            unsigned char dp1, unsigned char dp2, unsigned char dp3, unsigned char dp4);
void SSD_WriteDigitsGrouped(unsigned int val, unsigned char dp);
unsigned char SSD_GetDigitSegments(unsigned char d);
void SSD_ConfigurePins();
void SSD_Timer1Setup();
void SSD_WriteDecimal(unsigned int val);

#endif 

