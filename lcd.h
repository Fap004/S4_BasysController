/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    lcd.h

 **/
/* ************************************************************************** */

#ifndef _LCD_H  
#define _LCD_H

#ifdef __cplusplus
extern "C" {
#endif
    
    void LCD_WriteByte(unsigned char data);
    void LCD_Init();
    void LCD_SetCursor(unsigned char ligne, unsigned char col);
    void LCD_Print(char *str);
    
#ifdef __cplusplus
}
#endif

#endif 