#include <xc.h>
#include <stdint.h>
#include "timer2.h"
#define PIN_PULSADOR 5
#define LED_RC1 1
#define N_MAX 5

int main(void) {
    int puls_act, puls_ant;

    ANSELB &= ~(1 << PIN_PULSADOR);
    ANSELC = 0;
    TRISB = (1 << PIN_PULSADOR); //entrada (1)
    TRISC = 0; //salida (0)
    LATC = 0xFFFF; //LED desactivado (activo a nivel bajo)

    InicializarTimer2();
    
    INTCONbits.MVEC = 1; //pone CPU a multi-vector
    asm("ei"); //habilita interrupciones

    puls_ant = (PORTB >> PIN_PULSADOR) & 1;
    while (1) {
        puls_act = (PORTB >> PIN_PULSADOR) & 1;
        if ((puls_ant != puls_act) && (puls_act == 0)) {
            incrPulsac();
            if (getPulsac >= N_MAX) {
                LATCCLR = 1 << LED_RC1; //enciende LED
                iniContador4s();
                if(getSegundos()==4){
                    LATCSET = 1 << LED_RC1; //apago LED
                    stopContador4s();
                }
            }
        }
        puls_ant = puls_act;
    }
    return 0;
}