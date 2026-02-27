/* 
 * File:   newmain.c
 * Author: irene y guille
 *
 * Created on February 27, 2026, 9:35 AM
 */

#include <xc.h>
#include <stdint.h>

#define PIN_UART1 13
#define PIN_PULSADOR

int main(void){
    char c;
    uint32_t bits4; 
    
    ANSELB &= ~(1<<PIN_UART1);
    TRISB |= 1<<PIN_UART1;
    
    char cad[] = "Hola mundo";
    int puls=0, puls_ant;
    
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
        if (U1STAbits.URXDA != 0) {
            c = U1RXREG;
            bits4 = (uint32_t) c & 0x000F;
            LATC = (LATC & ~0x000F) | bits4;
        }
        puls_ant=puls;
        puls = (PORTB >> PIN_PULSADOR) & 0x1;
        if (puls<puls_ant){
            U1STAbits.UTXEN=1;
            for (int icad=0; cad[icad]!='\0'; icad++){
                while(U1STAbits.TRMT==1);
                U1TXREG=cad[icad];
            }
            U1STAbits.UTXEN=0;
        }
    }
    return 0;
}

