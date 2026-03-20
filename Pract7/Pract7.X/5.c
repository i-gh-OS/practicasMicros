/* 
 * File:   5.c
 * Author: irene
 *
 * Created on March 20, 2026, 5:21 PM
 */

#include <xc.h>
#include <stdint.h>
#include "Pic32Ini.h"
#define PIN_SERVO 15
#define PR2_20MS 49999
//#define T_ALTO_MIN 1250
#define T_ALTO_MAX 6250
static int angulo = -90;
static int t_alto;
static int direccion = 1; // 1 para incrementar (subir), -1 para
static int cuenta_20ms = 0;

int getTicks(void);

int main(void) {
    ANSELB &= ~(1 << PIN_SERVO);
    ANSELC &= ~0xF;
    LATA = 0;
    LATB = 0;
    LATC = 0xF;
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    RPB15R = 5;
    SYSKEY = 0x1CA11CA1;

    t_alto = 1250;

    OC1CON = 0;
    OC1R = t_alto;
    OC1RS = t_alto;
    OC1CON = 0x8006; // OC ON y sin faltas
    T2CON = 0;
    TMR2 = 0;
    PR2 = PR2_20MS;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
    IPC2bits.T2IP = 2;
    IPC2bits.T2IS = 1;
    T2CON = 0x8010;
    INTCONbits.MVEC=1;
    asm("ei");
    
    while(1) {
        asm("di");
        if (cuenta_20ms >= 50) {
            cuenta_20ms = 0; // Reiniciamos el contador de tiempo
            // Actualizamos el ángulo de 10º en 10º
            angulo += (10 * direccion);
            // Límites
            if (angulo >= 90) {
                angulo = 90;
                direccion = -1; // Ha llegado al tope derecho
            } else if (angulo <= -90) {
                angulo = -90;
                direccion = 1; // Ha llegado al tope izquierdo
            }
            // Conversor ángulo a tiempo
            t_alto = 1250 + ((angulo + 90) * (T_ALTO_MAX -
                    1250)) / 180;
            OC1RS = t_alto;
        }   
        asm("ei");
    }
}
__attribute__((vector(8), interrupt(IPL2SOFT), nomips16)) 
void interrT2(void) {
    IFS0bits.T2IF = 0;
    cuenta_20ms++;
}
