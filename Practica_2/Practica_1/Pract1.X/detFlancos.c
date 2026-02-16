/* 
 * File:   detFlancos.c
 * Author: laboratorios
 *
 * Created on 30 de enero de 2026, 17:30
 */

#include <xc.h>
#define PIN_PULSADOR 5

int main(void) {

    int pulsador_ant, pulsador_act;
    int cuenta = 0;

    TRISC = 0xFFF0;
    LATC = 0xFFFF;
    TRISB = 0xFFFF;

    pulsador_ant = (PORTB >> PIN_PULSADOR)&1;

    while (1) {

        pulsador_act = (PORTB >> PIN_PULSADOR)&1;
        if ((pulsador_act != pulsador_ant) && (pulsador_act == 0)) {
            cuenta++;
            if (cuenta > 15) {
                cuenta = 0;
            }
            LATC = ~cuenta;
        }
        pulsador_ant = pulsador_act;
    }
}

