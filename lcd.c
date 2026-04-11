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
    // set control pins as digital outputs.
    tris_LCD_DISP_RS = 0;
    tris_LCD_DISP_RW = 0;
    tris_LCD_DISP_EN = 0;
    
    // disable analog (set pins as digital))
    ansel_LCD_DISP_RS = 0;
    
    // default (IO) function for remapable pins
    rp_LCD_DISP_RS = 0;
    rp_LCD_DISP_RW = 0;
    rp_LCD_DISP_EN = 0;
    
    // make data pins digital (disable analog)
    ansel_LCD_DB2 = 0;
    ansel_LCD_DB4 = 0;
    ansel_LCD_DB5 = 0;
    ansel_LCD_DB6 = 0;
    ansel_LCD_DB7 = 0;
}

void LCD_WriteByte(unsigned char bData)
{
    DelayAprox10Us(5);  
	// Configure IO Port data pins as output.
   tris_LCD_DATA &= ~msk_LCD_DATA;
    DelayAprox10Us(5);  
	// clear RW
	lat_LCD_DISP_RW = 0;

    // access data as contiguous 8 bits, using pointer to the LSB byte of LATE register
    unsigned char *pLCDData = (unsigned char *)(0xBF886430);
    *pLCDData = bData;

    DelayAprox10Us(10);   

	// Set En
	lat_LCD_DISP_EN = 1;    

    DelayAprox10Us(5);
	// Clear En
	lat_LCD_DISP_EN = 0;

    DelayAprox10Us(5);
	// Set RW
	lat_LCD_DISP_RW = 1;
}

unsigned char LCD_ReadByte()
{
    unsigned char bData;
	// Configure IO Port data pins as input.
    tris_LCD_DATA |= msk_LCD_DATA;
	// Set RW
	lat_LCD_DISP_RW = 1;

	// set RW
	lat_LCD_DISP_RW = 1;    
    
	// Set En
	lat_LCD_DISP_EN = 1;

    DelayAprox10Us(50);   

    // Clear En
	lat_LCD_DISP_EN = 0;
  	bData = (unsigned char)(prt_LCD_DATA & (unsigned int)msk_LCD_DATA);
	return bData;
}

unsigned char LCD_ReadStatus()
{
	// Clear RS
	lat_LCD_DISP_RS = 0;
    
	unsigned char bStatus = LCD_ReadByte();
	return bStatus;
}

void LCD_WriteCommand(unsigned char bCmd)
{ 
	// Clear RS
	lat_LCD_DISP_RS = 0;

	// Write command byte
	LCD_WriteByte(bCmd);
}

void LCD_WriteDataByte(unsigned char bData)
{
	// Set RS 
	lat_LCD_DISP_RS = 1;

	// Write data byte
	LCD_WriteByte(bData);
}


void LCD_InitSequence(unsigned char bDisplaySetOptions)
{
	//	wait 40 ms

	DelayAprox10Us(40000);
	// Function Set
	LCD_WriteCommand(cmdLcdFcnInit);
	// Wait ~100 us
	DelayAprox10Us(10);
	// Function Set
	LCD_WriteCommand(cmdLcdFcnInit);
	// Wait ~100 us
	DelayAprox10Us(10);	// Display Set
	LCD_DisplaySet(bDisplaySetOptions);
	// Wait ~100 us
	DelayAprox10Us(10);
	// Display Clear
	LCD_DisplayClear();
	// Wait 1.52 ms
	DelayAprox10Us(160);
    // Entry mode set
	LCD_WriteCommand(cmdLcdEntryMode);
    	// Wait 1.52 ms
	DelayAprox10Us(160);
}

void LCD_DisplaySet(unsigned char bDisplaySetOptions)
{
	LCD_WriteCommand(cmdLcdCtlInit | bDisplaySetOptions);
}

void LCD_DisplayClear()
{
	LCD_WriteCommand(cmdLcdClear);
}

void LCD_ReturnHome()
{
	LCD_WriteCommand(cmdLcdRetHome);
}

void LCD_DisplayShift(unsigned char fRight)
{
	unsigned char bCmd = cmdLcdDisplayShift | (fRight ? mskShiftRL: 0);
	LCD_WriteCommand(bCmd);
}

void LCD_CursorShift(unsigned char fRight)
{
	unsigned char bCmd = cmdLcdCursorShift | (fRight ? mskShiftRL: 0);
	LCD_WriteCommand(bCmd);
}

void LCD_WriteStringAtPos(char *szLn, unsigned char idxLine, unsigned char idxPos)
{
	// crop string to 0x27 chars
	int len = strlen(szLn);
	if(len > 0x27)
	{
        szLn[0x27] = 0; // trim the string so it contains 40 characters 
		len = 0x27;
	}

	// Set write position
	unsigned char bAddrOffset = (idxLine == 0 ? 0: 0x40) + idxPos;
	LCD_SetWriteDdramPosition(bAddrOffset);

	unsigned char bIdx = 0;
	while(bIdx < len)
	{
		LCD_WriteDataByte(szLn[bIdx]);
		bIdx++;
	}
}

void LCD_SetWriteCgramPosition(unsigned char bAdr)
{
	unsigned char bCmd = cmdLcdSetCgramPos | bAdr;
	LCD_WriteCommand(bCmd);
}

void LCD_WriteBytesAtPosCgram(unsigned char *pBytes, unsigned char len, unsigned char bAdr)
{
	// Set write position
	LCD_SetWriteCgramPosition(bAdr);

	// Write the string of bytes that define the character to CGRAM
	unsigned char idx = 0;
	while(idx < len)
	{
		LCD_WriteDataByte(pBytes[idx]);
		idx++;
	}
}
