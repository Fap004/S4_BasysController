/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    adc.c

 **/
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "adc.h"

void ADC_Init_Manuel() {
    AD1CON1bits.ON = 0;     
    
    AD1CON1bits.SSRC = 0;  
    AD1CON1bits.ASAM = 0;   
    AD1CON1bits.FORM = 0;   
    
    AD1CON2 = 0;            
    AD1CON3bits.SAMC = 15;  
    AD1CON3bits.ADCS = 2;   
    
    IEC0bits.AD1IE = 0; 
    
    AD1CON1bits.ON = 1;     
}

int ADC_Read_Manuel(int canal) {
    int rawADC;

    AD1CHSbits.CH0SA = canal; 
    
    AD1CON1bits.SAMP = 1;     
    delay_us(10);             
    AD1CON1bits.SAMP = 0;    
    
    while (!AD1CON1bits.DONE); 
    
    rawADC = ADC1BUF0;      

    if (rawADC > 494 && rawADC < 530) {
        rawADC = 512;
    }
    
    return rawADC;       
}

int calculer_vitesse() {
    int rawADCY = ADC_Read_Manuel(17);
    int devY = 512 - rawADCY; 
    if (devY < 0) devY = 0; 

    int vitesse = (devY * 100) / 480; 
    if (vitesse > 100) vitesse = 100;
    return vitesse;
}

float calculer_angle_joystick() {
    int rawADCX = ADC_Read_Manuel(16); 
    int deviationX = rawADCX - 512;
    return ((float)deviationX * 45.0f) / 490.0f;
}