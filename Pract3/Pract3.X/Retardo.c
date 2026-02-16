/* 
 * File:   Retardo.c
 * Author: labmicros
 *
 * Created on February 6, 2026, 11:17 AM
 */

#include <xc.h>
#include <stdint.h>
#include "Pic32Ini.h"

int Retardo(uint16_t retardo_ms) {

    int t_PR=0;
    int preescalados[] = {1, 2, 4, 8, 16, 32, 64, 256};
    int i = 0, tckps= -1;
    T2CON = 0;
    TMR2 = 0;
    IFS0bits.T2IF = 0;

    if (retardo_ms != 0) {

        for (i = 0; i < 8; i++) {

            t_PR = ((retardo_ms*5000)/ preescalados[i])-1;

            if  (t_PR <= 65535) {
                tckps = i;
                break;
            } 
        }

        if (tckps==-1){
            return 1;
        }

    } else {
        return 0;
    }

    PR2 = t_PR;
    T2CON = 0x8000 | (tckps << 4);

    while (IFS0bits.T2IF == 0); //como hemos visto en clase, no hace falta poner nada dentro
    IFS0bits.T2IF = 0;
    T2CON = 0x0000;
    return 0;
}
