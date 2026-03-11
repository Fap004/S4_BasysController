/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    mef_mode.h

 **/
/* ************************************************************************** */

#ifndef _MEF_MODE_H  
#define _MEF_MODE_H

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef enum {
        joystick, 
        hybride 
    } Mode;
    
    extern Mode mode_actuel;
    extern volatile unsigned int setup_mode;
    
    void mef_mode();

#ifdef __cplusplus
}
#endif

#endif 