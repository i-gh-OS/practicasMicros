#include <xc.h>
#include "Pic32Ini.h" // Aquí se define PBCLK
#include "UART1simple.h"

#define PIN_U1RX     13 // U1RX se conecta a RB13
#define PIN_U1TX      7 // U1TX se conecta a RB7

// Variables compartidas interrupción -- bucle scan. Se usa un carácter
// para el receptor y una cadena para el transmisor.
#define TAM_CAD 80 // tamaño máxima cadena a transmitir
static char car_rx = '\0'; // \0 indica que no ha llegado nada nuevo
static char cad_tx[TAM_CAD];
static int i_cad_tx = 0; // índice para la cadena de transmisión

void InicializarUART1(int baudios) {
    // TO-DO: Seleccionar 16 o 4 en función de baudios

    U1BRG = PBCLK / 16 / baudios - 1;

    // Activamos las interrupciones del receptor.
    IFS1bits.U1RXIF = 0; // Borro flag por si acaso
    IEC1bits.U1RXIE = 1; // Habilito interrupciones
    IFS1bits.U1TXIF = 0; // Borro flag del tranmisor por si acaso

    IPC8bits.U1IP = 3; // Prioridad 3
    IPC8bits.U1IS = 1; // Subprioridad 1


    // Conectamos U1RX y U1TX a los pines RB13 y RB7 del micro
    ANSELB &= ~((1 << PIN_U1RX) | (1 << PIN_U1TX)); // Primero los configuramos como digitales
    TRISB |= 1 << PIN_U1RX; // Y RB13 como entrada, aunque el manual no dice nada de esto ??
    LATB |= 1 << PIN_U1TX; // Para que se quede a 1 mientras el transmisor esté inhabilitado.

    SYSKEY = 0xAA996655; // Se desbloquean los registros
    SYSKEY = 0x556699AA; // de configuración.
    U1RXR = 3; // U1RX conectado a RB13. Ojo: si se cambia el define esto se cambia a mano
    RPB7R = 1; // U1TX conectado a RB7.
    SYSKEY = 0x1CA11CA1; // Se vuelven a bloquear.

    U1STAbits.UTXISEL = 2; // Interrupción cuando FIFO vacía. 

    // Se habilitan receptor y transmisor
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    U1MODE = 0x8000; // Se arranca la UART
}

__attribute__((vector(32), interrupt(IPL3SOFT),
        nomips16))
void InterrupcionUART1(void) {
    if (IFS1bits.U1RXIF == 1) { // Ha interrumpido el receptor
        car_rx = U1RXREG;
        IFS1bits.U1RXIF = 0; // Y para terminar se borra el flag
    }
    if (IFS1bits.U1TXIF == 1) { // Ha interrumpido el transmisor 
        if (cad_tx[i_cad_tx] == '\0') { // Ha terminado la cadena
            IEC1bits.U1TXIE = 0; // Inhabilito int. TX para no entrar en bucle
            i_cad_tx = 0; // Se deja el índice preparado para la siguiente cadena
            cad_tx[i_cad_tx] = '\0'; // para no volver a enviar de nuevo la cadena cuando
            // interrumpa el receptor.
        } else {
            U1TXREG = cad_tx[i_cad_tx];
            i_cad_tx++;
        }
        IFS1bits.U1TXIF = 0; // Y para terminar se borra el flag
    }
}

/**
 * Comprueba si ha llegado un carácter nuevo por la UART y lo devuelve.
 * Si no ha llegado nada nuevo retorna un \0.
 *
 * @return  caracter recibido o \0 si no se ha recibido nada.
 */

char getcUART(void) {
    char car_ret;

    //asm(" di");
    car_ret = car_rx;
    if (car_ret != '\0') { // Ha llegado un nuevo carácter
        car_rx = '\0'; // lo pongo a \0 para darme cuenta cuando llegue uno nuevo
    }
    //asm(" ei");
    return car_ret;
}

/**
 * Copia una cadena de caracteres a la cadena compartida y habilita
 * el transmisor para que se envíe.
 * 
 * @param s cadena de caracteres a enviar
 */
void putsUART(char *ps) {
    char *pc;

    pc = cad_tx; // Uso pc para recorrer la cadena compartira
    while (*ps != '\0') {
        *pc = *ps;
        pc++;
        ps++;
    }

    IEC1bits.U1TXIE = 1; // habilito las interrupciones para que se
    // empiece a transmitir
    //IFS1bits.U1TXIF = 1;
}

void putcUART(char c) {
    char *pc;
    pc = cad_tx; // Uso pc para recorrer la cadena compartira
    *pc = c; //cad_tx[0]=c
    pc++;
    *pc = '\0'; //cad_tx[1]='\0'
    IEC1bits.U1TXIE = 1; // habilito las interrupciones para que se
    // empiece a transmitir
}
