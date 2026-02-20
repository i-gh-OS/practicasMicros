/* 
 * File:   main4.c
 * Author: labmicros
 *
 * Created on February 8, 2026, 18:11 PM
 */

 #include <xc.h>
#include "Retardo.h"
#include "Pic32Ini.h"

#define PIN_LED 0
#define PERIODO_MS 20

int main(void) {

    ANSELC = 0x0000;
    LATC = 0xFFFF; 
    TRISC = 0xFFF0;
    TRISA = 0x0000;
    TRISB = 0x0000;

    //uint16_t retardo_ms = 20, retardo_ant = 21;
    uint16_t on_ms = 0;

    while (1) {

        // ON
        LATC &= ~(1 << PIN_LED);
        Retardo(on_ms);

        // OFF
        LATC |= (1 << PIN_LED);
        Retardo(PERIODO_MS - on_ms);

        // actualizar on_ms para el efecto "latido"
        if (on_ms == PERIODO_MS) {
            dir = -1;
        }
        else if (on_ms == 0){
            dir = +1;
        }
        on_ms = (uint16_t)((int)on_ms + dir);
    }
    return 0;
}