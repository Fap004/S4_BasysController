/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    broches.c

 **/
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "broches.h"

void config_broches()
{
    /* DELs */
    TRISACLR = 0x00FF; 
    LATACLR = 0x00FF; 
    LATAbits.LATA7 = 1;
    
    /* BTNL (RB0) */
    TRISBbits.TRISB0 = 1;  
    ANSELBbits.ANSB0 = 0; 
    
    /* BTNC (RF0) */
    TRISFbits.TRISF0 = 1;  
    
    /* BTNR (RB8) */
    TRISBbits.TRISB8 = 1;  
    ANSELBbits.ANSB8 = 0;
    
    /* BTNU (RB1) */
    TRISBbits.TRISB1 = 1; 
    ANSELBbits.ANSB1 = 0; 
    
    /* LCD */
    TRISBbits.TRISB15 = 0; // RB15 (DISP_RS)
    ANSELBbits.ANSB15 = 0;  
    TRISDbits.TRISD5 = 0; // RD5 (DISP_RW)
    TRISDbits.TRISD4 = 0; // RD4 (DISP_EN)
    
    TRISECLR = 0x00FF; // RE0 à RE7    
    ANSELECLR = 0x00FC;   
    
    /* 7 segments */
    TRISBbits.TRISB12 = 0; // RB12
    ANSELBbits.ANSB12 = 0; 
    TRISBbits.TRISB13 = 0; // RB13
    ANSELBbits.ANSB13 = 0; 
    TRISAbits.TRISA9 = 0; // RA9
    TRISAbits.TRISA10 = 0; // RA10
    TRISGbits.TRISG12 = 0; // RG12
    TRISAbits.TRISA14 = 0; // RA14
    TRISDbits.TRISD6 = 0; // RD6
    TRISGbits.TRISG13 = 0; // RG13
    TRISGbits.TRISG15 = 0; // RG15
    TRISDbits.TRISD7 = 0; // RD7
    TRISDbits.TRISD13 = 0; // RD13
    TRISGbits.TRISG14 = 0; // RG14
    
    /* Accéléromètre */
    TRISGbits.TRISG0 = 1;
    
    /* JA4 et JA8 */
    TRISGbits.TRISG6 = 1;  
    ANSELGbits.ANSG6 = 1; 
    TRISGbits.TRISG7 = 1;  
    ANSELGbits.ANSG7 = 1;  
    
    /* UART */
    TRISFbits.TRISF12 = 0; 
    TRISFbits.TRISF13 = 1;
    
    RPF12R = 0b0010;       
    U4RXR = 0b1001;
    
}