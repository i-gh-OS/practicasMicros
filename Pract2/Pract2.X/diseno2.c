/* 
 * File:   diseno2.c
 * Author: laboratorios
 *
 * Created on 30 de enero de 2026, 18:15
 */

#include <xc.h>
#define PIN_PULSADOR 5

int main(void) {

    int pulsador_ant, pulsador_act;
    int posicion = 0;

    TRISC = 0xFFF0;
    LATC = 0xE;
    TRISB = 0xFFFF;

    pulsador_ant = (PORTB >> PIN_PULSADOR)&1;

    while (1) {

        pulsador_act = (PORTB >> PIN_PULSADOR)&1;
        if ((pulsador_act != pulsador_ant) && (pulsador_act == 0)) {
            posicion++;
            if (posicion > 3) {
                posicion = 0;
            }
            LATC = 0x000F&~(1<<posicion);
        }
        pulsador_ant = pulsador_act;
    }
    return 0;
}
