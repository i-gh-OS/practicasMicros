/* 
 * File:   main3.c
 * Author: labmicros
 *
 * Created on February 6, 2026, 12:24 AM
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

    uint16_t on_ms = 0;
    int dir = 1;

    while (1) {

        // ON
        LATC &= ~(1 << PIN_LED); //pongo 0 en el LED
        Retardo(on_ms); //espero 0s en 1ª iteracion 1ms en la 2ª...

        // OFF
        LATC |= (1 << PIN_LED); //pongo 1 en el LED
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

