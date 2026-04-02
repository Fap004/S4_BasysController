/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    uart.c

 **/
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "uart.h"
#include "broches.h"

void UART4_PutChar(unsigned char c) {
    
    while (U4STAbits.UTXBF) {
    }
    
    U4TXREG = c;
}

void UART4_PutString(const char* s) {
    
    while(*s != '\0') {      
        UART4_PutChar(*s);   
        s++;                 
    }
}

void UART_Init(unsigned int baudrate) {
    U4MODEbits.ON = 0;          
    U4MODEbits.BRGH = 0;        
    
    U4BRG = (48000000 / (16 * baudrate)) - 1; 

    U4MODEbits.PDSEL = 0;       // 8 bits, pas de parité
    U4MODEbits.STSEL = 0;       // 1 stop bit
    
    U4STAbits.UTXEN = 1;        
    U4STAbits.URXEN = 1;        
    U4MODEbits.ON = 1;          
}