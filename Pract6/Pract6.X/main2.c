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


int main(void) {

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

void ProcesaOrden(char orden[]){
    char respuesta[20];
    char puerto;
    int pin;
    int valor;

    orden[0] = toupper(orden[0]);
    orden[1] = toupper(orden[1]);
    orden[3] = toupper(orden[3]);

    if (orden[0] != 'P' || orden[1] != 'I') {
        putsUART("Instruccion Desconocida\n");
        return;
    }

    if (orden[2] != ',' || orden[4] != ',' || orden[5] == '\0') {
        putsUART("Error\n");
        return;
    }

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
    } else {
        valor = (PORTC >> pin) &1;
    }

    putsUART(respuesta);
}
