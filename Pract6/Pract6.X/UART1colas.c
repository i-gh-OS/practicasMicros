
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include "UART1colas.h"
#include "Pic32Ini.h"

void iniUART1(int baudios) {
    ANSELB &= ~((1 << 13) | (1 << 7)); 
    TRISB |= 1 << 13; 
    LATB |= 1 << 7; 
    TRISB &= ~(1 << 7);
    
    SYSKEY = 0xAA996655; 
    SYSKEY = 0x556699AA;
    U1RXR = 3; // U1RX conectado a RB13.
    RPB7R = 1; // U1TX conectado a RB7.
    SYSKEY = 0x1CA11CA1; 
    
    int brg;

    if (baudios > 38400){
        brg = 5000000 / (4 * baudios) - 1;
    } else {
        brg = 5000000 / (16 * baudios) - 1;   
    }

    U1BRG = brg;
    
    IFS1bits.U1RXIF = 0; // Borro flag por si acaso 
    IEC1bits.U1RXIE = 1; // Habilito interrupciones 
    IFS1bits.U1TXIF = 0; // Borro flag del transmisor
    IPC8bits.U1IP = 3; // Prioridad 3 
    IPC8bits.U1IS = 1; // Subprioridad 1
    U1STAbits.URXISEL = 0; // Interrupcion cuando llegue 1 char. 
    U1STAbits.UTXISEL = 2; // Interrupcion cuando FIFO vacia.
    U1STAbits.URXEN = 1; // Se habilita el receptor. 
    U1STAbits.UTXEN = 1; // Fuerza un 1er envio
    U1MODE = 0x8000; // Se arranca la UART
}

#define TAM_COLA 100 
static int icab_rx = 0, icol_rx = 0, icab_tx = 0, icol_tx = 0;
static char cola_rx[TAM_COLA], cola_tx[TAM_COLA];

__attribute__((vector(32), interrupt(IPL3SOFT), nomips16)) 
void InterrupcionUART1(void) {
    if (IFS1bits.U1RXIF == 1) { // Ha interrumpido el receptor
        if ((icab_rx + 1 == icol_rx) ||
                (icab_rx + 1 == TAM_COLA && icol_rx == 0)) {
            // La cola esta llena 
        } else {
            cola_rx[icab_rx] = U1RXREG; // Lee caracter de la UART 
            icab_rx++;
            if (icab_rx == TAM_COLA) {
                icab_rx = 0;
            }
        }
        IFS1bits.U1RXIF = 0; // Y para terminar se borra el flag
    }
    if (IFS1bits.U1TXIF == 1) { // Ha interrumpido el transmisor
        if (icol_tx != icab_tx) { // Hay datos nuevos 
            U1TXREG = cola_tx[icol_tx];
            icol_tx++;
            if (icol_tx == TAM_COLA) {
                icol_tx = 0;
            }
        } else { // Se ha vaciado la cola.
            IEC1bits.U1TXIE = 0; // Para evitar bucle sin fin 
        }
        IFS1bits.U1TXIF = 0; // Y para terminar se borra el flag
    }
}

char getcUART(void) {
    char c;
    asm("di");
    if (icol_rx != icab_rx) { // Hay datos nuevos 
        c = cola_rx[icol_rx];
        icol_rx++;
        if (icol_rx == TAM_COLA) {
            icol_rx = 0;
        }
    } else {
        c = '\0'; // no ha llegado nada 
    }
    asm("ei");
    return c;
}

void putsUART(char s[]) {
    uint8_t i = 0;
    asm("di");
    while (s[i] != '\0') {
        if ((icab_tx + 1 == icol_tx) ||
                (icab_tx + 1 == TAM_COLA && icol_tx == 0)) {
            break; // La cola esta llena. 
                // Se aborta el envio de los caracteres que restan 
        } else {
            cola_tx[icab_tx] = s[i]; // Copia el caracter en la cola
            i++;
            icab_tx++;
            if (icab_tx == TAM_COLA) {
                icab_tx = 0;
            }
        }
    }
    // Se habilitan las interrupciones del tx para comenzar a enviar 
    IEC1bits.U1TXIE = 1;
    asm("ei");
}


