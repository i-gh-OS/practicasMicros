/* 
 * File:   Main Practica XXXX Ej YYYY / Examen
 * Author: Poner nombre
 *
 */

#include <xc.h>
#include "Pic32Ini.h"
//Otros include?


//define parameters
#define PIN_PULSADOR  5

int main(void) {
    // Configuración del pulsador y los LEDs
    ANSELC &= ~0xF; // Pines de los LEDs como digitales
    ANSELB &= (1 << PIN_PULSADOR); // Pin del pulsador también como digital

    LATA = 0; // En el arranque dejamos todas las salidas no usadas a 0
    LATB = 0;
    LATC = 0xF; // Apago los LEDs de la placa

    // Pines como salidas
    TRISA = 0;
    TRISB = 1 << PIN_PULSADOR;
    TRISC = 0;

    //Inicializaciones
    int i = 0xDEAC;
    // Habilito las interrupciones
    //INTCONbits.MVEC = 1;
    //asm("ei");

    while (1) {
        i = 0xDEAC;
        i = i >> 4;
        i = i << 4;
        i &= 0x0CFF;
        i |= 0x1001;
    }
}


//Guía Timer
//void iniTimerx(void){ // Se configura el timer X
//  TxCON = ;
//  PRx = ; //𝑃𝑅=𝑇𝑖𝑒𝑚𝑝𝑜·𝑃𝐵𝐶𝐿𝐾·𝑃𝑟𝑒𝑒𝑠𝑐𝑎𝑙𝑎𝑑𝑜 - 1
//  TMRx = ;
//  IFS0bits.TxIF = ; // Se borra el flag
//  IEC0bits.TxIE = ; // Se habilitan las interrupciones del timer 
//  IPC2bits.TxIP = ; // Prioridad 
//  IPC2bits.TxIS = ; // Subprioridad 
//  TxCON = ;    // Tx on, tckps(div)
//}
//void __attribute__((vector(_TIMER_x_VECTOR), interrupt(IPLySOFT), nomips16)) InterrupcionTimerx(void) {
//   //Contenido Interrupcion
//}

//Guía OC
//void iniOCx(void){
//  SYSKEY=0xAA996655;
//  SYSKEY=0x556699AA;
//  RPB15R = 5; // Ejemplo OC1 conectado a RB15
//  SYSKEY=0x1CA11CA1;
//  
//  OC1CON = 0;
//  OC1R = ;     // Tiempo en alto 0,5ms (-90º) a 2,5ms (90º))
//  OC1RS = ;
//  OC1CON = 0x8006; // OC ON, modo PWM sin faltas T2
//  
//  T2CON = 0;
//  TMR2 = 0;
//  PR2 = 49999;     // Periodo de 20 ms 𝑃𝑅 =𝑇𝑖𝑒𝑚𝑝𝑜·𝑃𝐵𝐶𝐿𝐾/2 - 1
//  T2CON = 0x8010;  // T2 ON, Div = 2 
//}