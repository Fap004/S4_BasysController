#ifndef _LCD_H
#define _LCD_H

#define cmdLcdFcnInit       0x3C
#define cmdLcdCtlInit       0x0C
#define cmdLcdEntryMode     0x06
#define cmdLcdClear         0x01
#define cmdLcdSetDdramPos   0x80
#define displaySetOptionDisplayOn 0x4
#define LCD_SetWriteDdramPosition(bAddr) LCD_WriteCommand(cmdLcdSetDdramPos | bAddr)

void LCD_Init();
void LCD_InitSequence(unsigned char bDisplaySetOptions);
void LCD_ConfigurePins();
void LCD_WriteCommand(unsigned char bCmd);
void LCD_WriteByte(unsigned char bData);
void LCD_WriteDataByte(unsigned char bData);
void LCD_DisplaySet(unsigned char bDisplaySetOptions);
void LCD_DisplayClear();
void LCD_WriteStringAtPos(char *szLn, unsigned char idxLine, unsigned char bAdr);

#endif