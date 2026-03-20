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
#define T_ALTO_MIN 1250
#define T_ALTO_MAX 6250

int main(void) {
    int angulo = -90;
    int t_alto;
    int direccion = 1; // 1 para incrementar (subir), -1 para
    decrementar(bajar)
            int cuenta_20ms = 0; // Contador para medir el segundo
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
    // Posición inicial: -90º = 0.5 ms
    t_alto = T_ALTO_MIN;
    // Configuración OC1 en modo PWM
    OC1CON = 0;
    OC1R = t_alto;
    OC1RS = t_alto;
    OC1CON = 0x8006; // OC ON y sin faltas
    T2CON = 0;
    TMR2 = 0;
    PR2 = PR2_20MS;
    IFS0bits.T2IF = 0;
    T2CON = 0x8010;
    while (1) {
        // Comprobamos si el Timer2 ha completado un ciclo de 20ms
        if (IFS0bits.T2IF == 1) {
            IFS0bits.T2IF = 0;
            cuenta_20ms++;

            1 segundo
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
                t_alto = T_ALTO_MIN + ((angulo + 90) * (T_ALTO_MAX -
                        T_ALTO_MIN)) / 180;
                OC1RS = t_alto;
            }
        }
    }