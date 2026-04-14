#include <xc.h>
#include <sys/attribs.h>
#include <string.h>
#include "config.h"
#include "lcd.h"

void LCD_Init()
{
    LCD_ConfigurePins();
    LCD_InitSequence(displaySetOptionDisplayOn);
}

void LCD_ConfigurePins()
{
    tris_LCD_DISP_RS = 0;
    tris_LCD_DISP_RW = 0;
    tris_LCD_DISP_EN = 0;
    ansel_LCD_DISP_RS = 0;
    rp_LCD_DISP_RS = 0;
    rp_LCD_DISP_RW = 0;
    rp_LCD_DISP_EN = 0;
    ansel_LCD_DB2 = 0;
    ansel_LCD_DB4 = 0;
    ansel_LCD_DB5 = 0;
    ansel_LCD_DB6 = 0;
    ansel_LCD_DB7 = 0;
}

void LCD_WriteByte(unsigned char bData)
{
    DelayAprox10Us(5);
    tris_LCD_DATA &= ~msk_LCD_DATA;
    DelayAprox10Us(5);
    lat_LCD_DISP_RW = 0;
    unsigned char *pLCDData = (unsigned char *)(0xBF886430);
    *pLCDData = bData;
    DelayAprox10Us(10);
    lat_LCD_DISP_EN = 1;
    DelayAprox10Us(5);
    lat_LCD_DISP_EN = 0;
    DelayAprox10Us(5);
    lat_LCD_DISP_RW = 1;
}

void LCD_WriteCommand(unsigned char bCmd)
{
    lat_LCD_DISP_RS = 0;
    LCD_WriteByte(bCmd);
}

void LCD_WriteDataByte(unsigned char bData)
{
    lat_LCD_DISP_RS = 1;
    LCD_WriteByte(bData);
}

void LCD_DisplaySet(unsigned char bDisplaySetOptions)
{
    LCD_WriteCommand(cmdLcdCtlInit | bDisplaySetOptions);
}

void LCD_DisplayClear()
{
    LCD_WriteCommand(cmdLcdClear);
}

void LCD_InitSequence(unsigned char bDisplaySetOptions)
{
    DelayAprox10Us(40000);
    LCD_WriteCommand(cmdLcdFcnInit);
    DelayAprox10Us(10);
    LCD_WriteCommand(cmdLcdFcnInit);
    DelayAprox10Us(10);
    LCD_DisplaySet(bDisplaySetOptions);
    DelayAprox10Us(10);
    LCD_DisplayClear();
    DelayAprox10Us(160);
    LCD_WriteCommand(cmdLcdEntryMode);
    DelayAprox10Us(160);
}

void LCD_WriteStringAtPos(char *szLn, unsigned char idxLine, unsigned char idxPos)
{
    int len = strlen(szLn);
    if(len > 0x27)
    {
        szLn[0x27] = 0;
        len = 0x27;
    }
    unsigned char bAddrOffset = (idxLine == 0 ? 0 : 0x40) + idxPos;
    LCD_SetWriteDdramPosition(bAddrOffset);
    unsigned char bIdx = 0;
    while(bIdx < len)
    {
        LCD_WriteDataByte(szLn[bIdx]);
        bIdx++;
    }
}