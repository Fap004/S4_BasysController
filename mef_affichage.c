/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    mef_affichage.c

 **/
/* ************************************************************************** */

#include <xc.h>
#include <stdio.h>
#include <sys/attribs.h>
#include "config.h"
#include "mef_affichage.h"
#include "lcd.h"
#include "delay.h"

Affichage affichage_actuel = km_h;

void mef_affichage(int vitesse)
{
    char buffer[17];
    float v_convertie;
    
    int valBTNL = PORTBbits.RB0;                                       
    int valBTNR = PORTBbits.RB8;
    
    switch(affichage_actuel) {
        case km_h:
            LATAbits.LATA6 = 1; LATAbits.LATA5 = 0; LATAbits.LATA4 = 0;      
            sprintf(buffer, "Vitesse:%3d km/h", vitesse);         
            if (valBTNR) { 
                while(PORTBbits.RB8);              
                delay_ms(10);                      
                affichage_actuel = m_s;                 
            } 
            else if (valBTNL) { 
                while(PORTBbits.RB0);              
                delay_ms(10);                       
                affichage_actuel = m_p_h;                                     
            }
            break;
        case m_s:
            LATAbits.LATA6 = 0; LATAbits.LATA5 = 1; LATAbits.LATA4 = 0;                   
            v_convertie = (float)vitesse * 0.2778f;
            sprintf(buffer, "Vitesse:%4.1f m/s ", (double)v_convertie); 
            if (valBTNR) { 
                while(PORTBbits.RB8);              
                delay_ms(10);                      
                affichage_actuel = m_p_h;                               
            } 
            else if (valBTNL) { 
                while(PORTBbits.RB0);              
                delay_ms(10);                       
                affichage_actuel = km_h;                                       
            }
            break;  
        case m_p_h:
            LATAbits.LATA6 = 0; LATAbits.LATA5 = 0; LATAbits.LATA4 = 1;
            v_convertie = (float)vitesse * 0.6213f;
            sprintf(buffer, "Vitesse:%3d mph  ", (int)v_convertie);
            if (valBTNR) { 
                while(PORTBbits.RB8);              
                delay_ms(10);                      
                affichage_actuel = km_h;                               
            } 
            else if (valBTNL) { 
                while(PORTBbits.RB0);              
                delay_ms(10);                       
                affichage_actuel = m_s;                                      
            }
            break;
    }
    LCD_SetCursor(0, 0);
    LCD_Print(buffer);
    delay_ms(100);
}

