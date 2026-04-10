
#include <xc.h>
#include <stdint.h>
#include "Pic32Ini.h"
#define PIN_PULS_INC 5 
#define PIN_PULS_DEC 7 
#define PIN_SERVO 15  

int main(void) {
    int puls_inc_ant, puls_inc_act;
    int puls_dec_ant, puls_dec_act;

    int angulo = -90;
    int t_alto;

    ANSELB &= ~((1 << PIN_PULS_INC) | (1 << PIN_PULS_DEC) | (1 << PIN_SERVO));
    ANSELC &= ~0xF;
    LATA = 0;
    LATB = 0;
    LATC = 0xF;
    TRISA = 0;
    TRISB = (1 << PIN_PULS_INC) | (1 << PIN_PULS_DEC);
    TRISC = 0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    RPB15R = 5;
    SYSKEY = 0x1CA11CA1;

    t_alto = 1250;

    OC1CON = 0;
    OC1R = t_alto;
    OC1RS = t_alto;
    OC1CON = 0x8006;

    T2CON = 0;
    TMR2 = 0;
    PR2 = 49999;
    T2CON = 0x8010;
    puls_inc_ant = (PORTB >> PIN_PULS_INC) & 1;
    puls_dec_ant = (PORTB >> PIN_PULS_DEC) & 1;
    while (1) {
        puls_inc_act = (PORTB >> PIN_PULS_INC) & 1;
        puls_dec_act = (PORTB >> PIN_PULS_DEC) & 1;
        int actualizar_pwm = 0;
        if ((puls_inc_act != puls_inc_ant) &&(puls_inc_act == 0)) {
            angulo += 20;
            if (angulo > 90) {
                angulo = -90;
            }
            actualizar_pwm = 1;
        }
        if ((puls_dec_act != puls_dec_ant) &&
                (puls_dec_act == 0)) {
            angulo -= 10;
            if (angulo < -90) {
                angulo = 90;
            }
            actualizar_pwm = 1;
        }
        if (actualizar_pwm == 1) {
            t_alto = 1250 + ((angulo + 90) * (6250 - 1250)) / 180;
            OC1RS = t_alto;
        }
        puls_inc_ant = puls_inc_act;
        puls_dec_ant = puls_dec_act;
    }
}

