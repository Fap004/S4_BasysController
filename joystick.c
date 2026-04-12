#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "joystick.h"

void ADC_Init()
{
	AD1CON1	=	0; 
    AD1CON1bits.SSRC = 7;   // Internal counter ends sampling and starts conversion (auto convert)
    AD1CON1bits.FORM = 0;   // Integer 16-bit
	// Setup for manual sampling
	AD1CSSL	=	0;
	AD1CON3	=	0x0002;     // ADC Conversion Clock Select bits: TAD = 6 TPB
	AD1CON2	=	0;
    AD1CON2bits.VCFG = 0;   // Voltage Reference Configuration bits: VREFH = AVDD and VREFL = AVSS
	// Turn on ADC
    AD1CON1bits.ON = 1;
} 

unsigned int ADC_AnalogRead(unsigned char analogPIN)
{
    int adc_val = 0;
    
    IEC0bits.T2IE = 0;
    AD1CHS = analogPIN << 16;       // AD1CHS<16:19> controls which analog pin goes to the ADC
 
    AD1CON1bits.SAMP = 1;           // Begin sampling
    while( AD1CON1bits.SAMP );      // wait until acquisition is done
    while( ! AD1CON1bits.DONE );    // wait until conversion is done
 
    adc_val = ADC1BUF0;
    IEC0bits.T2IE = 1;
    return adc_val;
}

signed char ADC_8_Bits_Signed(unsigned int adc_val)
{
    int temp;

    if (adc_val > 1023) adc_val = 1023;

    if (adc_val > 487 && adc_val < 520) 
    {
        adc_val = 512;
    }
    
    temp = ((int)adc_val - 512) / 4;

    return (signed char)temp;
}

signed char ADC_GetValX()
{
    return ADC_8_Bits_Signed(ADC_AnalogRead(19));
}

signed char ADC_GetValY()
{
    return ADC_8_Bits_Signed(ADC_AnalogRead(17));
}