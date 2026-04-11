#ifndef _MEF_H  
#define _MEF_H
    
typedef enum {
    joystick, 
    hybride 
} Mode;

typedef enum {
    km_h, 
    m_s, 
    m_p_h
} Affichage;

extern Mode mode_actuel;
extern Affichage affichage_actuel;

void mef_mode();
void mef_affichage(int vitesse);

#endif 