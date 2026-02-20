/* 
 * File:   main1.c
 * Author: labmicros
 *
 * Created on February 6, 2026, 8:17 AM
 */

#include <xc.h>
#include "Pic32Ini.h"

#define PIN_LED 3

int main(void){
    ANSELC = 0x0000; 
    LATC = 0xFFFF; 
    TRISC = 0xFFF0;
    TRISA = 0x0000;
    TRISB = 0x0000;
    
    T2CON = 0;
    TMR2 = 0;
    IFS0bits.T2IF = 0;
    //IFS0 &= ~(1 << 9);
    PR2 = 19531;
    T2CON = 0x8070;
    
    while (1) {
        while(IFS0bits.T2IF == 0);
        IFS0bits.T2IF = 0;
        LATC ^= (1<<PIN_LED);
    }
    return 0;
}

