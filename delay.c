/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    delay.c

 **/
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "delay.h"

void delay_ms(unsigned int ms) {                
    unsigned int tWait = (48000000 / 2000) * ms;     
    unsigned int tStart = _CP0_GET_COUNT();
    while ((_CP0_GET_COUNT() - tStart) < tWait);
}

void delay_us(unsigned int us) {
    unsigned int tWait = (48000000 / 2000000) * us; 
    unsigned int tStart = _CP0_GET_COUNT();
    while ((_CP0_GET_COUNT() - tStart) < tWait);
}