/* 
 * File:   main5.c
 * Author: irene y guille
 *
 * Created on 13 de marzo de 2026, 12:14
 */

#include <xc.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "UART1colas.h"

#define BAUDIOS 9600
#define TAM_ORDEN 20

int toInt(char c);
void ProcesaOrden(char orden[]);

int main(void) {
    char c;
    char orden[TAM_ORDEN];
    int i = 0;

    ANSELB = 0;
    ANSELC = 0;

    INTCONbits.MVEC = 1;
    iniUART1(BAUDIOS);
    asm("ei");

    while (1) {
        c = getcUART();
        if (c != '\0') {
            if (c == '\n') {
                orden[i] = '\0'; //cerrar string
                ProcesaOrden(orden);
                i = 0; //preparar siguiente orden
            } else {
                if (i < TAM_ORDEN - 1) {
                    orden[i] = c;
                    i++;
                } else {
                    // buffer lleno -> error y reinicio
                    putsUART("Error\n");
                    i = 0;
                }
            }
        }
    }
    return 0;
}

int toInt(char c) {
    c = toupper(c);
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

void ProcesaOrden(char orden[]) {
    char respuesta[20];
    char tipo;
    char puerto;
    int pin;
    int valor;

    //pasar a mayusculas
    orden[0] = toupper(orden[0]);
    orden[1] = toupper(orden[1]);
    orden[3] = toupper(orden[3]);

    if (orden[0] != 'P') {
        putsUART("Instruccion Desconocida\n");
        return;
    }

    tipo = orden[1];

    //PD y PO
    if (tipo == 'D' || tipo == 'O') {
        // Formato: PX,<puerto>,<pin>,<valor>
        if (orden[2] != ',' || orden[4] != ',' || orden[6] != ',' || orden[8] != '\0') {
            putsUART("Error\n");
            return;
        }

        puerto = orden[3];
        pin = toInt(orden[5]);
        valor = orden[7] - '0';

        if (puerto != 'B' && puerto != 'C') {
            putsUART("Puerto no soportado\n");
            return;
        }

        if (pin < 0 || pin > 15) {
            putsUART("Error\n");
            return;
        }

        if (valor != 0 && valor != 1) {
            putsUART("Error\n");
            return;
        }

        if (tipo == 'D') {
            if (puerto == 'B') {
                if (valor == 1) {
                    TRISB |= (1 << pin);
                } else {
                    TRISB &= ~(1 << pin);
                }
            } else {
                if (valor == 1) {
                    TRISC |= (1 << pin);
                } else {
                    TRISC &= ~(1 << pin);
                }
            }

            putsUART("OK\n");
            return;
        }

        if (tipo == 'O') {
            if (puerto == 'B') {
                if (valor == 1) {
                    LATBSET = (1 << pin);
                } else {
                    LATBCLR = (1 << pin);
                }
            } else {
                if (valor == 1) {
                    LATCSET = (1 << pin);
                } else {
                    LATCCLR = (1 << pin);
                }
            }

            putsUART("OK\n");
            return;
        }
    }

    //PI
    if (tipo == 'I') {
        // Formato: PI,<puerto>,<pin>
        if (orden[2] != ',' || orden[4] != ',' || orden[6] != '\0') {
            putsUART("Error\n");
            return;
        }

        puerto = orden[3];
        pin = toInt(orden[5]);

        if (puerto != 'B' && puerto != 'C') {
            putsUART("Puerto no soportado\n");
            return;
        }

        if (pin < 0 || pin > 15) {
            putsUART("Error\n");
            return;
        }

        if (puerto == 'B') {
            valor = (PORTB >> pin) & 1;
        } else {
            valor = (PORTC >> pin) & 1;
        }

        sprintf(respuesta, "PI,%d\n", valor);
        putsUART(respuesta);
        return;
    }
    putsUART("Instruccion Desconocida\n");
}