/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    mef_affichage.h

 **/
/* ************************************************************************** */

#ifndef _MEF_AFFICHAGE_H  
#define _MEF_AFFICHAGE_H

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef enum {
        km_h, 
        m_s, 
        m_p_h
    } Affichage;
    
    extern Affichage affichage_actuel;
    extern volatile unsigned int setup_affichage;
    
    void mef_affichage(int vitesse);

#ifdef __cplusplus
}
#endif

#endif 