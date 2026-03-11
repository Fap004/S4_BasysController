/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    lcd.c

 **/
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "lcd.h"
#include "delay.h"

void LCD_WriteByte(unsigned char data) {
    PORTE = data; // 8 bits -> RE0 à RE7              
    LATDbits.LATD4 = 1;         
    delay_us(20);               
    LATDbits.LATD4 = 0;         
    delay_us(100);              
}

void LCD_Init() {
    delay_ms(50);              
    
    LATDbits.LATD5 = 0; // Writing Mode      
    LATBbits.LATB15 = 0; // Instructions      

    LCD_WriteByte(0b00111000); // Function Set -> 8 bits, 2 lignes     
    delay_ms(5);
    LCD_WriteByte(0b00001100); // Display ON/OFF -> Display ON, Cursor OFF      
    delay_ms(1);
    LCD_WriteByte(0b00000001); // Clear Display      
    delay_ms(5);               
}

void LCD_SetCursor(unsigned char ligne, unsigned char col) {
    unsigned char addr;

    if (ligne == 0) { addr = 0b10000000 + col; } //ligne 0, colonne 0
    else { addr = 0b11000000 + col; } //ligne 1, colonne 0
    LATBbits.LATB15 = 0; // Instructions       
    LCD_WriteByte(addr);
}

void LCD_Print(char *str) {
    LATBbits.LATB15 = 1; // Data      
    while(*str) {
        LCD_WriteByte(*str++);
    }
}