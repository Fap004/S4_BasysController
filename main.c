#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "config_bits.h"

#include "lcd.h"
#include "ssd.h"

#include "joystick.h"
#include "acl.h"

#include "uart.h"
#include "spi.h"

#include "mef.h"
#include "delay.h"

int main() 
{
    LCD_Init();
    ADC_Init();
    SPIJA_Init();
    ACL_Init();
    SSD_Init();
    UART_Init(400000);
    
    TRISAbits.TRISA0 = 0; TRISAbits.TRISA1 = 0; 
    TRISAbits.TRISA5 = 0; TRISAbits.TRISA6 = 0; 
    TRISAbits.TRISA7 = 0;
    
    TRISFbits.TRISF0 = 1;
    TRISBbits.TRISB0 = 1; ANSELBbits.ANSB0 = 0; 
    TRISBbits.TRISB8 = 1; ANSELBbits.ANSB8 = 0; 
    
    macro_enable_interrupts();
    
//    signed char joyX, joyY, aclX, aclY;
//    char buffer[17];
    
    while(1)
    {
        mef_mode();         
        mef_affichage(uart_data); 
        
        //joyX = ADC_GetValX();
        //joyY = ADC_GetValY();
        
        //aclX = ACL_GetRawX_8bit();
        //aclY = ACL_GetRawY_8bit();
        
//        sprintf(buffer, "AX:%4d JX:%4d ", aclX, joyX);
//        LCD_WriteStringAtPos(buffer, 0, 0);
//        
//        sprintf(buffer, "AY:%4d JY:%4d ", aclY, joyY);
//        LCD_WriteStringAtPos(buffer, 1, 0);
        
//        //unsigned int affichage = (unsigned int)abs(joyX);
//        unsigned int affichage = (unsigned int)abs(aclX);
//        SSD_WriteDecimal(affichage); 
//        
//        SPIJA_WriteTrame(joyX, joyY);
    }
    return 0;
}