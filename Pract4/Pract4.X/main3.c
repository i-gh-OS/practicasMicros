/*
 * File:   main3.c
 * Author: Irene y Guille
 *
 * Created on 20 de febrero de 2026, 17:21
 */

#include <xc.h>
#include <stdint.h>
#include "Pic32Ini.h"
#define PIN_PULSADOR 5
#define LED_RC1 1
#define LED_RC0 0
#define N_MAX 5

static int pulsac = 0;
static int tienes_contar=0;
static int segundos=0;

__attribute__((vector(_TIMER_2_VECTOR), interrupt(IPL2SOFT), nomips16))
void InterrupcionTimer2(void) {
    LATCINV = (1 << LED_RC0);
    pulsac = 0;
    IFS0bits.T2IF = 0;
    if (tienes_contar){
        segundos++;
    }
}

int main(void) {
    int puls_act, puls_ant;

    ANSELB &= ~(1 << PIN_PULSADOR);
    ANSELC = 0;
    TRISB = (1 << PIN_PULSADOR); //entrada (1)
    TRISC = 0; //salida (0)
    LATC = 0xFFFF; //LED desactivado (activo a nivel bajo)

    //incializacion timer 2 a 1s
    T2CON = 0;
    TMR2 = 0;
    PR2 = 19530; //preescalado 256
    //inicializacion interrupciones timer 2
    IPC2bits.T2IP = 2;
    IPC2bits.T2IS = 0;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1; //habilita interrupcion individual
    T2CON = 0x8070; //empieza timer

    INTCONbits.MVEC = 1; //pone CPU a multi-vector
    asm("ei"); //habilita interrupciones

    puls_ant = (PORTB >> PIN_PULSADOR) & 1;
    while (1) {
        puls_act = (PORTB >> PIN_PULSADOR) & 1;
        if ((puls_ant != puls_act) && (puls_act == 0)) {
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