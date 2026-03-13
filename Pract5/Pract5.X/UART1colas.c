
#include <xc.h>
#include "UART1colas.h"
#include "Pic32Ini.h"

#define TAM_COLA = 100;
static int icab_rx=0, icol_rx=0, icab_tx=0, icol_tx=0;
static cola_rx[TAM_COLA], cola_tx[TAM_COLA];

void iniUART1(void){

}

__attribute__((vector(32), interrupt(IPL3SOFT), nompis16)) void InterrupcionUART1(void){
    if(IFS1BITS.U1RX1F==1){
        if(icab_rx+1==icol_rx)
        ||(icol_rx=0 && icab_rx+1==TAM_COLA){
            //cola llena
        } else {
            cola_rx[icab_rx]=U1RXREG; //meto primer byte
            icad_rx++;
            if (icad_rx==TAM_COLA){
                icab_rx=0; //inicio de la cola de nuevo
            }
        }
    }
}
char getUART(void){
    char c;
    if(icol_rx != icab_rx){
        c=cola_rx[icol_rx];
        icol_rx++;
        
    }
}

        