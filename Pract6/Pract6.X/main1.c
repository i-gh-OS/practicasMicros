/* 
 * File:   newmain.c
 * Author: irene y guille
 *
 * Created on February 24, 2026, 7:53 PM
 */

#include <xc.h>
#include <stdint.h>

#define PIN_UART1 13

int main(void){
    char c;
    uint32_t bits4; 
    
    ANSELB &= ~(1<<PIN_UART1);
    TRISB |= 1<<PIN_UART1;
    
    ANSELC = 0;
    TRISC = 0;
    LATC = 0xFFFF;
    
    SYSKEY = 0XAA996655;
    SYSKEY = 0X556699AA;
    U1RXR = 3;
    SYSKEY = 0X1CA11CA1; //vuelvo a bloquear
    
    U1BRG = 32; //9600 baudios
    U1MODE = 0x8000; //ON, control de flujo estandar, v estandar, 8N1
    U1STAbits.URXEN=1;
    
    while(1){
        while(U1STAbits.URXDA==0);
        c = U1RXREG;
        bits4 = (uint32_t)c & 0x000F;
        LATC = (LATC & ~0x000F) | bits4; //tenemos que limpiar antes de hacer el OR
                                         // lo hacemos en una sola instrucc para que no
                                         // se enciendan los bits (aunque en teoria se encienden?)
    }
    return 0;
}

