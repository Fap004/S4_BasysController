/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    7segments.h

 **/
/* ************************************************************************** */

#ifndef _SEVENSEGMENTS_H  
#define _SEVENSEGMENTS_H

#ifdef __cplusplus
extern "C" {
#endif
    
    void SevenSegments_Update();
    void SevenSegments_SetDigit(int n);
    void SevenSegments_SetNumber(int n);
    
#ifdef __cplusplus
}
#endif

#endif 