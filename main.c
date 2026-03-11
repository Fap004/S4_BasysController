/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    main.c

 **/
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>
#include <math.h>
#include <stdio.h>
#include "config_bits.h"
#include "config.h"
#include "broches.h"
#include "mef_affichage.h"
#include "mef_mode.h"
#include "lcd.h"
#include "timer1.h"
#include "accelerometre.h"
#include "i2c.h"
#include "adc.h" 
#include "uart.h"

#define RAD_TO_DEG 57.29577951f

int main() {
    float angleDeg;
    int angleAffichage;
    int vitesse;
    char uartBuffer[64];
    float v_convertie;
    
    config_broches();
    LCD_Init();
    Timer1_Init();
    I2C_Init();
    ACL_Init();
    ADC_Init_Manuel(); 
    UART_Init(9600);
    
    macro_enable_interrupts();
    
    while(1){
        vitesse = calculer_vitesse();

        if (mode_actuel == hybride) {
            angleDeg = calculer_angle_accel();
        } 
        else {
            angleDeg = calculer_angle_joystick();
        }
 
        angleAffichage = (int)fabsf(angleDeg);
        if (angleAffichage > 45) angleAffichage = 45;
        
        SevenSegments_SetNumber(angleAffichage);
        mef_affichage(vitesse); 
        mef_mode();
        
        if (affichage_actuel == km_h) { 
            sprintf(uartBuffer, "Angle: %2d deg | Vitesse: %3d km/h\r\n", angleAffichage, vitesse);
            UART4_PutString(uartBuffer);
        } else if (affichage_actuel == m_s) {
            v_convertie = (float)vitesse * 0.2778f;
            sprintf(uartBuffer, "Angle: %2d deg | Vitesse:%4.1f m/s\r\n", angleAffichage, (double)v_convertie);
            UART4_PutString(uartBuffer);
        } else {
            v_convertie = (float)vitesse * 0.6213f;
            sprintf(uartBuffer, "Angle: %2d deg | Vitesse: %3d mph\r\n", angleAffichage, (int)v_convertie);
            UART4_PutString(uartBuffer);
        }
        
        delay_ms(20);
    }
    return 0;
}