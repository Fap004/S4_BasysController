#ifndef _JOYSTICK_H   
#define _JOYSTICK_H

void ADC_Init();
unsigned int ADC_AnalogRead(unsigned char analogPIN);
signed char ADC_8_Bits_Signed(unsigned int adc_val);
signed char ADC_GetValX();
signed char ADC_GetValY();

#endif 