/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    mef_affichage.c

 **/
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "mef_mode.h"
#include "lcd.h"
#include "delay.h"

extern Mode mode_actuel = joystick;

void mef_mode(){
    
    int valBTNC = PORTFbits.RF0;                         
    
    switch(mode_actuel) {
        case joystick:
            LATAbits.LATA0 = 1; LATAbits.LATA1 = 0;     
            LCD_SetCursor(1, 0);
            LCD_Print("Mode: Joystick ");
            if (valBTNC) { 
                while(PORTFbits.RF0);              
                delay_ms(10);                      
                mode_actuel = hybride;                                
            } 
            break;
        case hybride:
                LATAbits.LATA0 = 0; LATAbits.LATA1 = 1;                  
                LCD_SetCursor(1, 0);
                LCD_Print("Mode: Hybride ");
            if (valBTNC) { 
                while(PORTFbits.RF0);              
                delay_ms(10);                      
                mode_actuel = joystick;                               
            } 
            break;
    }
}

