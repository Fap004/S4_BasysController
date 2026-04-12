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
    UART_Init(460800);
    
    TRISAbits.TRISA0 = 0; TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA5 = 0; TRISAbits.TRISA6 = 0; 
    TRISAbits.TRISA7 = 0;
    
    TRISDbits.TRISD15 = 1;
    TRISBbits.TRISB0 = 1; ANSELBbits.ANSB0 = 0; 
    TRISBbits.TRISB8 = 1; ANSELBbits.ANSB8 = 0; 
    
    macro_enable_interrupts();
    
    while(1)
    {
        mef_mode();         
        mef_affichage(uart_data); 
    }
    return 0;
}