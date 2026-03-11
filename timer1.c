/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    timer1.c

 **/
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "timer1.h"
#include "7segments.h"

int compteur = 0;

void __ISR(_TIMER_1_VECTOR, IPL2AUTO) Timer1ISR(void) 
{  
   SevenSegments_Update();
   IFS0bits.T1IF = 0; 
}

void Timer1_Init() {
    T1CON = 0;
    T1CONbits.TCKPS = 0b10;
    PR1 = 2251;
    TMR1 = 0;
    IPC1bits.T1IP = 2;
    IPC1bits.T1IS = 0;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    T1CONbits.ON = 1;
}