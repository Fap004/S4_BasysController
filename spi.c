#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "spi.h"
#include "leds.h"

void SPIJA_Init()
{
    SPIJA_ConfigurePins();
    SPIJA_ConfigureSPI(1000000, 0, 1); // configures SPI to work at 1 Mhz, polarity 0 and edge 1.
}

void SPIJA_ConfigureSPI(unsigned int spiFreq, unsigned char pol, unsigned char edge)
{
    SPI2BRG = PB_FRQ / (2 * spiFreq) - 1;
    // configures SPI2
    SPI2CONbits.CKP = pol;    // SPI Clock Polarity
    SPI2CONbits.CKE = edge;   // SPI Clock Edge    
    SPI2CONbits.SMP = 0;      // SPI Data Input Sample Phase 
    SPI2CONbits.MSTEN = 1;    // Master
    SPI2CONbits.MODE16 = 0;   // 8 bit transfer
    SPI2CONbits.MODE32 = 0;   // 8 bit transfer
    SPI2CON2bits.AUDEN = 0;   // Audio protocol is disabled
    SPI2CONbits.ON = 1;       // enable SPI
}

void SPIJA_ConfigurePins()
{
    // Configure SPIJA signals as digital outputs.
    tris_SPIJA_CE = 0;
    tris_SPIJA_SCK = 0;
    tris_SPIJA_SI = 0;
    
    // Configure SPIJA signals as digital inputs.
    tris_SPIJA_SO = 1;
    
    // Configure remapable pins
    rp_SPIJA_SI = 0x06; // RPC1R = 0110 = SDO2
    rp_SPIJA_SO = 0x0A;// SDI2R = 1010 = RPC4
    
    ansel_SPIJA_SCK = 0;
    
    PMCONbits.ON = 0;
    RPG6R = 0;
    CM1CONbits.ON = 0;
}

unsigned char SPIJA_RawTransferByte(unsigned char bVal)
{
    while(!SPI2STATbits.SPITBE);	// wait for TX buffer to be empty
    SPI2BUF = bVal;
    while(!SPI2STATbits.SPIRBF);	// wait for RX buffer to be empty
    return SPI2BUF;
}

void SPIJA_TransferBytes(int bytesNumber, unsigned char *pbRdData, unsigned char *pbWrData)
{
    int i;
    lat_SPIJA_CE = 0; // Activate SS
    OnLed(6);
    for(i = 0; i< bytesNumber; i++)
    {
        pbRdData[i] = SPIJA_RawTransferByte(pbWrData[i]);
    }
    lat_SPIJA_CE = 1; // Deactivate SS
}

void SPIJA_Close()
{
    SPI2CONbits.ON = 0; // disable SPI
}


/* *****************************************************************************
 End of File
 */
