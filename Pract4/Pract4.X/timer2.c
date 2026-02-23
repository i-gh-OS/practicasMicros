/* 
 * File:   timer2.c
 * Author: Irene y Guille
 *
 * Created on 23 de febrero de 2026, 10:58
 */

#include <stdint.h>
#include "timer2.h"
#include <xc.h>

static uint32_t pulsac=0;
static uint32_t segundos=0;

void InicializarTimer2(void) {
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
}

__attribute__((vector(_TIMER_2_VECTOR), interrupt(IPL2SOFT), nomips16))
void InterrupcionTimer2(void) {
    IFS0bits.T2IF = 0;
    // LATCINV = (1 << LED_RC0);
    pulsac=0;
}

uint32_t getPulsac(void){
    return pulsac;
}

void cuentaSegundos(void){
    segundos++;
}

uint32_t getSegundos(void){
    return segundos;
}
    