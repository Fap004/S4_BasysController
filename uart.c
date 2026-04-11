#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>

#include "config.h"
#include "uart.h"

volatile char uart_data = 0;

void __ISR(_UART_4_VECTOR, IPL2AUTO) UART4_RX_ISR(void) 
{
    if (U4STAbits.URXDA) 
    {
        uart_data = U4RXREG;
    }
    
    IFS2bits.U4RXIF = 0; 
}

void UART_Init(unsigned int baudrate) 
{
    U4MODEbits.ON = 0;          
    U4MODEbits.BRGH = 0;        
    
    U4BRG = (48000000 / (16 * baudrate)) - 1; 

    U4MODEbits.PDSEL = 0;       
    U4MODEbits.STSEL = 0;       
          
    U4STAbits.URXEN = 1;        
    U4MODEbits.ON = 1;      
      
    IPC9bits.U4IP = 2;    
    IPC9bits.U4IS = 0;     
    IFS2bits.U4RXIF = 0;    
    IEC2bits.U4RXIE = 1;   
    
    TRISFbits.TRISF13 = 1;
    U4RXR = 0b1001;
}