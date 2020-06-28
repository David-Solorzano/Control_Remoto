/*
 * File:   control.c
 * Author: jairo
 *
 * Created on June 27, 2020, 5:42 PM
 */


#include <xc.h>
#include "LibreriaMicros.h"

//Freq = 8MHz => Tosc = 125ns
//Min TAD = 0.8us -> 8Tosc = 1us :D
//Min TACQ = 2.45 ?s -> 4us :D

void main(void) {
    USART_Init(9600);
    
    int lectura = 0;
    int umbralNuevo = 0;
    int umbralViejo = 0;
    INTCONbits.GIE = 1;             //Habilita todos los interrupts
    INTCONbits.RBIF = 0;            //Pone la flag del port change en 0
    INTCONbits.RBIE = 1;            //Habilita el port change interrupt           
    INTCONbits.INT0F = 0;
    INTCONbits.INT0E = 1;
    INTCON3bits.INT1F = 0;
    INTCON3bits.INT1E = 1;
    INTEDG0 = 0;
    INTEDG1 = 1;
    
    ADCON1 = 0b1110;                //AN0 analógico
    ADCON0bits.CHS = 0;             //AN0
    ADCON2bits.ADFM = 0;            //Justificado izuierda
    ADCON2bits.ADCS = 0b001;        //Reloj = 8Tosc
    ADCON2bits.ACQT = 0b010;        //Tacq = 4Tad
    ADCON0bits.ADON = 1;            //enciende ADC
    
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    TRISBbits.RB2 = 0;
    TRISBbits.RB4 = 1;
    TRISBbits.RB5 = 1;
    TRISBbits.RB6 = 1;
    TRISBbits.RB7 = 1;
    
    USART_Tx(6);
    
    while(1){
        ADCON0bits.GO_DONE = 1;
        while(ADCON0bits.GO_DONE == 1);
        umbralViejo = umbralNuevo;
        lectura = ADRESH;
        umbralNuevo = lectura / 51;
        if (umbralNuevo != umbralViejo){
            if (lectura < 51){
                USART_Tx("6");
                LATBbits.LATB2 ^= 1;
            }
            else if(lectura < 102){
                USART_Tx("7");
                LATBbits.LATB2 ^= 1;
            }
            else if(lectura < 154){
                USART_Tx("8");
                LATBbits.LATB2 ^= 1;
            }
            else if(lectura < 205){
                USART_Tx("9");
                LATBbits.LATB2 ^= 1;
            }
            else {
                USART_Tx("10");
            }
        }
    }
}

void __interrupt() ISR(){
    if (INT0F){
        USART_Tx("0");                //Adelante
        INT0F = 0;
        LATBbits.LATB2 ^= 1;
    }
    if (INT1F){
        USART_Tx("1");                //Atrás
        INT1F = 0;
        LATBbits.LATB2 ^= 1;
    }
    if (RBIF){
        if (!PORTBbits.RB4){
            USART_Tx("2");            //Izquierda
            LATBbits.LATB2 ^= 1;
        }
        else if (!PORTBbits.RB5){
            USART_Tx("3");            //Derecha
            LATBbits.LATB2 ^= 1;
        }
        else if (!PORTBbits.RB6){
            USART_Tx("4");            //Toggle Luces
            LATBbits.LATB2 ^= 1;
        }
        else if (!PORTBbits.RB7){
            USART_Tx("5");            //Toggle modo luces
            LATBbits.LATB2 ^= 1;
        }
        
        RBIF = 0;
    }
}
