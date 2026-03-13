/* 
 * File:   main1.c
 * Author: irene y guille
 *
 * Created on 13 de marzo de 2026, 12:32
 */

#include <xc.h>
#include <stdint.h>
#include "Pic32Ini.h"
#include "UART1colas.h"

static int baudios=9600;

int main(void) {
    iniUART1(baudios);
    //prueba    
    asm("ei");
    INTCON.MVEC =1;

    while (1) {
        char c = getcUART();
        if (c != '\0') {
            putsUART(c);
        }
    }
    return 0;
}
