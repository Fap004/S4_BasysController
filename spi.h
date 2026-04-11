#ifndef _SPIJA_H    
#define _SPIJA_H

void SPIJA_Init();
void SPIJA_ConfigureSPI(unsigned int spiFreq, unsigned char pol, unsigned char edge);
unsigned char SPIJA_TransferByte(unsigned char bVal);
void SPIJA_TransferBytes(int bytesNumber, unsigned char *pbRdData, unsigned char *pbWrData);
void SPIJA_Close();
void SPIJA_ConfigurePins();
void SPIJA_WriteTrame(signed char angle, signed char vitesse);

#endif 
