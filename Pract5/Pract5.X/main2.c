/* 
 * File:   newmain.c
 * Author: irene y guille
 *
 * Created on February 27, 2026, 9:13 AM
 */

#include <xc.h>
#include <stdint.h>
#define PIN_PULSADOR

int main(void){
    char cad[] = "Hola mundo";
    int puls=0, puls_ant;
    
    ANSELB &= ~(1<<PIN_PULSADOR);
    TRISB |= 1<<PIN_PULSADOR;
    
    SYSKEY = 0XAA996655;
    SYSKEY = 0X556699AA;
    RPB7R = 1;
    SYSKEY = 0X1CA11CA1; //vuelvo a bloquear
    
    U1BRG = 32; //9600 baudios
    U1MODE = 0x8000; //ON, control de flujo estandar, v estandar, 8N1
    
    while(1){
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


