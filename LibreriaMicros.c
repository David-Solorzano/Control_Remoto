#include <xc.h>
#include "LibreriaMicros.h"
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000L

void USART_Init(long baud){
    //Pines
    TRISCbits.RC6 = 0; //Tx salida
    TRISCbits.RC7 = 1; //Rx entrada
    
    //Baud
    SPBRG = (unsigned char)((_XTAL_FREQ/baud)/64)-1; 
    
    //Configuracion
    TXSTAbits.BRGH = 0;
    TXSTAbits.SYNC = 0; //asincrono
    RCSTAbits.SPEN = 1; //enable    
    
    //Tx
    TXSTAbits.TX9 = 0; //8 bits
    TXSTAbits.TXEN = 1; //habilitar transmision
    
    //Rx
    RCSTAbits.RC9 = 0; //8 bits
    RCSTAbits.CREN = 1;//activa rx
}

void USART_Tx(char data){
    TXREG = data;
}

char USART_Rx(){
    while((!RCIF));
    return RCREG;
}

void timer_init(){
    TMR1H = TMR1L = 0; //reset
    T1CONbits.T1CKPS1 = 0; //prescaler 1
    T1CONbits.T1CKPS0 = 0;
    TMR1IF = 0;
    PIE1bits.TMR1IE = 1; //enable interrupt
    IPR1bits.TMR1IP = 0;
    T1CONbits.TMR1ON = 0; //enciende el timer
    
}
