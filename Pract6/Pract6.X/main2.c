/* 
 * File:   main5.c
 * Author: irene y guille
 *
 * Created on 13 de marzo de 2026, 12:14
 */

/*
 * programa para controlar los pines de los puertos B y C
 * de la tarjeta desde el PC o el movil
 */

#include <xc.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "UART1colas.h"

#define baudios 9600

int main(void) {
    ANSELB = 0;
    ANSELC = 0;
    TRISC = 0;
    TRISB = 0;
    INTCONbits.MVEC =1;
    asm("ei");
    
    iniUART1(baudios);
    return 0;
}

int toInt(char c) {
    c = toupper(c);

    if (c >= '0' && c <= '9') {
        return c - '0'; //devuelve int
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }

    return -1; //error
}
    static int valor = 0;
void ProcesaOrden(char orden[]){
    char respuesta[20];
    char puerto;
    int pin;
    int direccion;


    orden[0] = toupper(orden[0]);
    orden[1] = toupper(orden[1]);
    orden[3] = toupper(orden[3]);

    if (orden[0] != 'P') {
        putsUART("Instruccion Desconocida\n");
        return;
    }
    if (orden[2] == ',' || orden[4] == ',' || orden[6] == ',' || orden[8] == '\n') {
        putsUART("Error\n");
        return;
        if (orden[1] != 'D' || orden[1] != 'O') {
            putsUART("Instruccion desconocida\n");
            return;
        }
        
        puerto = orden[3];
        pin = toInt(orden[5]);
        direccion = orden[7];
                
        if (puerto != 'B' && puerto != 'C') {
            putsUART("Puerto no soportado\n");
            return;
        }        
        
        if (pin < 0 || pin > 15) { //comprueba si pin es valido
            putsUART("Error\n");
            return;
        }
        
        if (orden[1] == 'O') {
            if (puerto == 'B'){
                if (direccion == 1){
                    LATBSET = 1 << pin;
                    return;
                }
                if (direccion == 0) {
                    LATBCLR = 1 << pin;
                    return;
                } else {
                    putsUART("Error\n");
                    return;
                }
            } else {
                if (direccion == 1) {
                    LATCSET = 1 << pin;
                    return;
                }
                if (direccion == 0) {
                    LATCCLR = 1 << pin;
                    return;
                } else {
                    putsUART("Error\n");
                    return;
                }
            }
        }

        if (orden[1] == 'D') {
            if (puerto == 'B') {
                if (direccion == 1){
                    TRISB |= 1 << pin;
                    return;
                }
                if (direccion == 0) {
                    TRISB &= ~(1 << pin);
                    return;
                } else {
                    putsUART("Error\n");
                    return;
                }
            } else {
                if (direccion == 1) {
                    TRISC |= 1 << pin;
                    return;
                }
                if (direccion == 0) {
                    TRISC &= ~(1 << pin);
                    return;
                } else {
                    putsUART("Error\n");
                    return;
                }
            }
        }
    }
    if (orden[2] == ',' || orden[4] == ',' || orden[6] == '\n') {
        puerto = orden[3];
        pin = toInt(orden[5]);
        if (puerto != 'B' && puerto != 'C') {
            putsUART("Puerto no soportado\n");
            return;
        }

        if (pin < 0 || pin > 15) { //comprueba si pin conv es valido
            putsUART("Error\n");
            return;
        }

        if (puerto == 'B') {
            valor = (PORTB >> pin) &1;
            return;
        } else {
            valor = (PORTC >> pin) &1;
            return;
        }
    }
    else {
        putsUART("Instruccion desconocida\n");
        return;
    }

    putsUART(respuesta);
}
