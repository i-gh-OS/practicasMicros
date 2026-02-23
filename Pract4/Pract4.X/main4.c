#include <xc.h>
#include <stdint.h>
#include "timer2.h"
#define PIN_PULSADOR 5
#define LED_RC1 1
#define N_MAX 5

static int pulsac = 0;
static int tienes_contar=0;
static int segundos=0;


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
            getPulsac();
            asm("di");
            pulsac++;
            if (pulsac >= N_MAX) {
                LATCCLR = 1 << LED_RC1; //enciende LED
                tienes_contar = 1;
            }
            asm("ei");  
        }
        puls_ant = puls_act;

        if (segundos >= 4) {
            asm("di");
            LATCSET = 1 << LED_RC1; //apago LED
            tienes_contar = 0;
            segundos = 0;
            asm("ei");
        }
    }
    return 0;
}