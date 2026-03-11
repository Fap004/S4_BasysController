/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    7segments.c

 **/
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "7segments.h"

static int valeur_a_afficher = -1;

void SevenSegments_SetDigit(int n) {
    // Éteindre les cathodes
    LATGbits.LATG12 = 1; LATAbits.LATA14 = 1; LATDbits.LATD6  = 1; 
    LATGbits.LATG13 = 1; LATGbits.LATG15 = 1; LATDbits.LATD7  = 1;     
    LATDbits.LATD13 = 1; LATGbits.LATG14 = 1; 
    
    // Allumer les cathodes correspondantes aux chiffres
    switch(n) {
        case 0:
            LATGbits.LATG12 = 0; LATAbits.LATA14 = 0; 
            LATDbits.LATD6 = 0; LATGbits.LATG13 = 0;  
            LATGbits.LATG15 = 0; LATDbits.LATD7 = 0;  
            break;
        case 1: 
            LATAbits.LATA14 = 0; LATDbits.LATD6 = 0; 
            break; 
        case 2: 
            LATGbits.LATG12 = 0; LATAbits.LATA14 = 0; 
            LATGbits.LATG13 = 0; LATGbits.LATG15 = 0; 
            LATDbits.LATD13 = 0; 
            break; 
        case 3: 
            LATGbits.LATG12 = 0; LATAbits.LATA14 = 0;
            LATDbits.LATD6 = 0;LATGbits.LATG13 = 0; 
            LATDbits.LATD13 = 0;
            break;
        case 4: 
            LATAbits.LATA14 = 0; LATDbits.LATD6 = 0; 
            LATDbits.LATD7 = 0; LATDbits.LATD13 = 0; 
            break; 
        case 5: 
            LATGbits.LATG12 = 0; LATDbits.LATD6 = 0; 
            LATGbits.LATG13 = 0; LATDbits.LATD7 = 0; 
            LATDbits.LATD13 = 0; 
            break; 
        case 6: 
            LATGbits.LATG12 = 0; LATDbits.LATD6 = 0; 
            LATGbits.LATG13 = 0; LATGbits.LATG15 = 0; 
            LATDbits.LATD7 = 0; LATDbits.LATD13 = 0; 
            break; 
        case 7: 
            LATGbits.LATG12 = 0; LATAbits.LATA14 = 0; 
            LATDbits.LATD6 = 0; 
            break; 
        case 8: 
            LATGbits.LATG12 = 0; LATAbits.LATA14 = 0; 
            LATDbits.LATD6 = 0; LATGbits.LATG13 = 0; 
            LATGbits.LATG15 = 0; LATDbits.LATD7 = 0; 
            LATDbits.LATD13 = 0; 
            break;
        case 9:
            LATGbits.LATG12 = 0; LATAbits.LATA14 = 0; 
            LATDbits.LATD6 = 0; LATGbits.LATG13 = 0; 
            LATDbits.LATD7 = 0;LATDbits.LATD13 = 0; 
            break; 
    }
}

void SevenSegments_Update() {
    static int index = 0;
    
    // Éteindre les anodes
    LATBbits.LATB12 = 1; 
    LATBbits.LATB13 = 1; 
    LATAbits.LATA9  = 1; 
    LATAbits.LATA10 = 1;
    
    // Éteindre anodes si inutilisées
    if (valeur_a_afficher < 0) {
        return; 
    }
    
    // Affichage de AN0 et AN1
    if (index == 0) {
        SevenSegments_SetDigit(valeur_a_afficher % 10);
        LATBbits.LATB12 = 0; 
    } else {
        SevenSegments_SetDigit((valeur_a_afficher / 10) % 10);
        LATBbits.LATB13 = 0; 
    }
    index = (index + 1) % 2;
}

void SevenSegments_SetNumber(int n) {
    valeur_a_afficher = n;
}