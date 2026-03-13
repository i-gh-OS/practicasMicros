/* 
 * File:   main4.c
 * Author: irene y guille
 *
 * Created on February 27, 2026, 9:50 AM
 */

#include <xc.h>
#include <stdint.h>

#define PIN_UART1 13
#define PIN_PULSADOR 5

int main(void){
    char c;
    
    ANSELB &= ~(1<<PIN_UART1);
    TRISB |= 1<<PIN_UART1;
    
    
    ANSELB &= ~(1<<PIN_PULSADOR);
    TRISB |= 1<<PIN_PULSADOR;
    
    ANSELC = 0;
    TRISC = 0;
    LATC = 0xFFFF;
    
    SYSKEY = 0XAA996655;
    SYSKEY = 0X556699AA;
    U1RXR = 3;
    RPB7R = 1;    
    SYSKEY = 0X1CA11CA1;
    
    U1BRG = 32; 
    U1MODE = 0x8000; 
    U1STAbits.URXEN=1;
    
    while(1){
        int a=0;
        if (U1STAbits.URXDA != 0) {
            c = U1RXREG;
            a=1;
            //bits4 = (uint32_t) c & 0x000F;
            //LATC = (LATC & ~0x000F) | bits4;
        }
        if(a){
            a=0;
            U1STAbits.UTXEN=1;
            U1TXREG=c;
            while(U1STAbits.TRMT==0);
            U1STAbits.UTXEN=0;
        }
    }
    return 0;
}

