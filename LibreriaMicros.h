
// more than once.  
#ifndef USARTlib_H
#define	USARTlib_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <pic18f4550.h>

void USART_Init(long baud);
void USART_Tx(char data);
char USART_Rx();
void timer_init();


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

