#include <xc.h>
#include <stdint.h>
#include "Pic32Ini.h"
#define PIN_PULS 5
#define PIN_SERVO 15
int main(void) {
    int puls_ant, puls_act;
    int angulo = -90;
    int t_alto;
    ANSELB &= ~((1 << PIN_PULS) | (1 << PIN_SERVO));
    ANSELC &= ~0xF;
    LATA = 0;
    LATB = 0;
    LATC = 0xF;
    TRISA = 0;
    TRISB = (1 << PIN_PULS);
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
    puls_ant = (PORTB >> PIN_PULS) & 1;
    while (1) {
        puls_act = (PORTB >> PIN_PULS) & 1;
        if ((puls_act != puls_ant) && (puls_act == 0)) {
            angulo += 20;
            if (angulo > 90) {
                angulo = -90;
            }
            
            t_alto = 1250 + ((angulo + 90) * (6250 - 1250)) / 180;
            OC1RS = t_alto;
        }
        puls_ant = puls_act;
    }
}
