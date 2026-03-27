/* 
 * File:   main2.c
 * Author: irene
 *
 * Created on January 23, 2026, 6:43 PM
 */

#include <xc.h>
#define PIN_PULSADOR 5

int main(void) {
    
    int pulsador;
    TRISC = 0xFFF0;
    LATC = 0x000F;
    TRISB = 0xFFFF;
    
    while (1){
        pulsador = (PORTB >> PIN_PULSADOR)&1;
        if (pulsador==0) {
            LATC &= ~1;
        }
        else {
          LATC |= 1;
        }    
    }
    return 0;
}
