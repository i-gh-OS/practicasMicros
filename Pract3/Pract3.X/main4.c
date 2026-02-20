/* 
 * File:   main4.c
 * Author: labmicros
 *
 * Created on February 8, 2026, 18:11 PM
 */

#include <xc.h>
#include "Retardo.h"
#include "Pic32Ini.h"

#define PIN_RC0 0
#define PERIODO_MS 20
#define PIN_RC3 3

int main(void) {

    ANSELC = 0x0000;
    LATC = 0xFFFF; 
    TRISC = 0xFFF0;
    TRISA = 0x0000;
    TRISB = 0x0000;

    uint16_t on_ms = 0;
    uint16_t ticks = 0;
    int dir = 1;

    while (1) {

        // RC0 ON
        LATC &= ~(1 << PIN_RC0);
        Retardo(on_ms);

        // RC0 OFF
        LATC |= (1 << PIN_RC0);
        Retardo(PERIODO_MS - on_ms);

        // latido
        if (on_ms == PERIODO_MS) {
            dir = -1;
        }
        else if (on_ms == 0){
            dir = +1;
        }
        on_ms = (uint16_t)((int)on_ms + dir);

        // parpadeo RC3 de 2s con base 20ms
        ticks++;
        if (ticks==100){ //100*20ms=2s
            LATC ^= (1 << PIN_RC3); 
            ticks = 0;
        }
    }
    return 0;
}

