/* ************************************************************************** */
/** Descriptive File Name

  @Author
    Louis-Félix Goneau (gonl2802)

  @File Name
    uart.h

 **/
/* ************************************************************************** */

#ifndef _UART_H  
#define _UART_H

#ifdef __cplusplus
extern "C" {
#endif
    
    void UART4_PutChar(unsigned char c);
    void UART4_PutString(const char* s);
    void UART_Init(unsigned int baudrate);
    
#ifdef __cplusplus
}
#endif

#endif 