#include <xc.h>
#include <sys/attribs.h>

#include "config.h"
#include "mef.h"
#include "lcd.h"
#include "acl.h"
#include "joystick.h"
#include "ssd.h"
#include "spi.h"

Mode mode_actuel = joystick;
Affichage affichage_actuel = km_h;

void mef_mode() {
    int valBTNC = PORTFbits.RF0;
    int valSW1 = PORTFbits.RF5;
    
    static int valBTNC_prec = 0;
    
    if (valBTNC == 1 && valBTNC_prec == 0) 
    {
        mode_actuel = (mode_actuel == joystick) ? hybride : joystick;
    }
    
    valBTNC_prec = valBTNC;

    LATAbits.LATA0 = (mode_actuel == joystick);
    LATAbits.LATA1 = (mode_actuel == hybride);
    
    signed char angle, vitesse;

    if (mode_actuel == joystick) {
        angle = ADC_GetValX();
        vitesse = ADC_GetValY();
        LCD_WriteStringAtPos("Mode: Joystick  ", 1, 0); 
    } 
    else { 
        angle = ADC_GetValX();
        vitesse = ACL_GetRawY_8bit();
        LCD_WriteStringAtPos("Mode: Hybride   ", 1, 0);
    }
    
    SSD_WriteDecimal((unsigned int)abs(angle));
    
    if (valSW1){
        SPIJA_WriteTrame(angle, vitesse);
        LCD_WriteStringAtPos("S", 0, 15);
    } else {
        LCD_WriteStringAtPos(" ", 0, 15);
    }
}

void mef_affichage(int vitesse) 
{
    char buffer[16];
    float v_convertie;
    int valBTNL = PORTBbits.RB0;
    int valBTNR = PORTBbits.RB8;
    static int L_prec = 0, R_prec = 0;

    if (valBTNR == 1 && R_prec == 0) 
    {
        if (affichage_actuel == km_h) affichage_actuel = m_s;
        else if (affichage_actuel == m_s) affichage_actuel = m_p_h;
        else affichage_actuel = km_h;
    }
    
    if (valBTNL == 1 && L_prec == 0) 
    {
        if (affichage_actuel == km_h) affichage_actuel = m_p_h;
        else if (affichage_actuel == m_p_h) affichage_actuel = m_s;
        else affichage_actuel = km_h;
    }
    
    R_prec = valBTNR; L_prec = valBTNL;

    switch(affichage_actuel) 
    {
        case km_h:
            LATAbits.LATA7 = 1; LATAbits.LATA6 = 0; LATAbits.LATA5 = 0;
            sprintf(buffer, "V:%3d km/h ", vitesse);
            break;
        case m_s:
            LATAbits.LATA7 = 0; LATAbits.LATA6 = 1; LATAbits.LATA5 = 0;
            v_convertie = (float)vitesse * 0.2778f;
            sprintf(buffer, "V:%3d m/s ", (int)v_convertie);
            break;
        case m_p_h:
            LATAbits.LATA7 = 0; LATAbits.LATA6 = 0; LATAbits.LATA5 = 1;
            v_convertie = (float)vitesse * 0.6213f;
            sprintf(buffer, "V:%3d mph ", (int)v_convertie);
            break;
    }
    
    LCD_WriteStringAtPos(buffer, 0, 0); 
}