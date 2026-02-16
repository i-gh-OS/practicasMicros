/* 
 * File:   main2.c
 * Author: labmicros
 *
 * Created on February 6, 2026, 9:11 AM
 */

#include <xc.h>
#include "Pic32Ini.h"
#include "Retardo.h"

#define PIN_LED 3

int main(void){
    
    ANSELC = 0x0000;
    LATC = 0xFFFF;
    TRISC = 0xFFF0; 
    TRISA = 0x0000;
    TRISB = 0x0000;
    
    uint16_t retardo_ms = 1000;
    
    while (1) {
        Retardo(retardo_ms);
        LATC ^= (1<<PIN_LED);
    }
    return 0;
}

