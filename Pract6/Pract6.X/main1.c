/* 
 * File:   main1.c
 * Author: irene y guille
 *
 * Created on 13 de marzo de 2026, 12:32
 */

#include <xc.h>
#include "Pic32Ini.h"
#include "UART1colas.h"

#define baudios 9600

char getcUART(void);
void putsUART(char s[]);
void InicializarUART1(int baudios);

int main(void) {
    iniUART1(baudios);
    //prueba
    while (1) {
        char c = getcUART();
        if (c != '\0') {
            putsUART(c);
        }
    }
    return 0;
}
