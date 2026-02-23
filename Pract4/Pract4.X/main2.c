/* 
 * File:   main2.c
 * Author: irene
 *
 * Created on 20 de febrero de 2026, 10:22
 */

#include <xc.h>
#include "Pic32Ini.h"
#define PIN_PULSADOR 5
#define LED_RC0 0
#define LED_RC3 3
#define LED_RC2 2

__attribute__((vector(_TIMER_2_VECTOR), interrupt(IPL2SOFT), nomips16))
void InterrupcionTimer2(void){
    IFS0bits.T2IF = 0;
    LATCINV = (1<<LED_RC3);
}
__attribute__((vector(_TIMER_3_VECTOR), interrupt(IPL4SOFT), nomips16))
void InterrupcionTimer3(void){
    IFS0bits.T3IF = 0;
    LATCINV = (1<<LED_RC2);
}

int main(void){
    int pulsador;
    asm("di"); //deshabilita interrupciones para evitar
               //problemas con registros compartidos
    ANSELB &= ~(1<<PIN_PULSADOR);
    ANSELC &= ~(1 << LED_RC0) | (1 << LED_RC3)| (1 << LED_RC2);
    TRISB |= (1<<PIN_PULSADOR); //entrada (1)
    TRISC &= ~(1 << LED_RC0) | (1 << LED_RC3)| (1 << LED_RC2); //salida (0)
    LATC |= (1 << LED_RC0) | (1 << LED_RC3)| (1 << LED_RC2); //LED desactivado (activo a nivel bajo)
    
    //incializacion timer 2 a 1s
    T2CON = 0;
    TMR2 = 0;
    PR2 = 19530; //preescalado 256
    //inicializacion interrupciones timer 2
    IPC2bits.T2IP = 2;
    IPC2bits.T2IS = 0;
    IFS0bits.T2IF = 0;
    INTCONbits.MVEC = 1; //pone CPU a multi-vector
    IEC0bits.T2IE = 1; //habilita interrupcion individual
    T2CON = 0x8070; //empieza timer
    
    //incializacion timer 3 a 500ms
    T3CON = 0;
    TMR3 = 0;
    PR3 = 39061; //preescalado 64
    //inicializacion interrupciones timer 3
    IPC3bits.T3IP = 4;
    IPC3bits.T3IS = 0;
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 1; //habilita interrupcion individual
    T3CON = 0x8060; //empieza timer, div. 6
    
    asm("ei"); //habilita interrupciones
    
    while(1){
        pulsador = (PORTB >> PIN_PULSADOR)&1;
        if(pulsador == 0){
            //LATC &= ~(1<<LED_RC0); //LED activado
            LATCCLR = (1<<LED_RC0);
        }else{
            //LATC |= 1<<LED_RC0; //LED desactivado
            LATCSET = (1<<LED_RC0);
        }
    }
    return 0;
}