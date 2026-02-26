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
static uint8_t juegoActivo=0;

void InicializarTimer2(void) {
    //incializacion timer 2 a 1s
    TMR2 = 0;
    T2CON = 0;
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
    pulsac=0; //se reinician las pulsaciones cada segundo
    if (juegoActivo) segundos++; //para ver cuando llegamos a 4s
}

uint32_t getPulsac(void){
    uint32_t c_pulsac;
    asm("di");
    c_pulsac = pulsac;
    asm("ei");
    return c_pulsac;
}

void incrPulsac(void){
    asm("di");
    pulsac++; //vamos incrementando hasta que se ponga a cero (cada segundo)
    asm("ei");
}

uint32_t getSegundos(void){
    uint32_t c_segundos;
    asm("di");
    c_segundos = segundos;
    asm("ei");
    return c_segundos;
}

void iniContador4s(void){
    asm("di");
    segundos=0;
    juegoActivo=1;
    asm("ei");
}

void stopContador4s(void){
    asm("di");
    segundos=0;
    juegoActivo=0; //asi la interrupcion deja de contar
    asm("ei");
}
    