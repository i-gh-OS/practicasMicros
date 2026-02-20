/* 
 * File:   main1.c
 * Author: irene
 *
 * Created on February 16, 2026, 9:46 AM
 */

#include <xc.h>
#include "Pic32Ini.h"
#define PIN_PULSADOR 5
#define LED_RC0 0
#define LED_RC3 3

__attribute__((vector(_TIMER_2_VECTOR), interrupt(IPL2SOFT), nomips16))
void InterrupcionTimer2(void){
    IFS0bits.T2IF = 0;
    LATC ^= (1<<LED_RC3);
    //LATCINV = (1<<LED_RC3);
}

int main(void){
    int pulsador;
    asm("di"); //deshabilita interrupciones para evitar
               //problemas con registros compartidos
    ANSELB &= ~(1<<PIN_PULSADOR);
    ANSELC &= ~(1 << LED_RC0) | (1 << LED_RC3);
    TRISB |= (1<<PIN_PULSADOR); //entrada (1)
    TRISC &= ~1; //salida (0)
    LATC |= (1 << LED_RC0) | (1 << LED_RC3); //LED desactivado (activo a nivel bajo)
    
    //incializacion timer 2 a 1s
    T2CON = 0;
    TMR2 = 0;
    PR2 = 19530; //preescalado 256
    
    //inicializacion interrupciones timer 2
    IPC2bits.T2IP = 2;
    IPC2bits.T2IS = 0;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1; //habilita interrupcion individual
    INTCONbits.MVEC = 1; //pone CPU a multi-vector
    
    T2CON = 0x8070; //empieza timer
    asm("ei"); //habilita interrupciones
    
    while(1){
        pulsador = (PORTB >> PIN_PULSADOR)&1;
        if(pulsador == 0){
            LATC &= ~(1<<LED_RC0); //LED activado
            //LATCCLR = (1<<LED_RC0);
        }else{
            LATC |= 1<<LED_RC0; //LED desactivado
            //LATCSET = (1<<LED_RC0);
        }
    }
    return 0;
}