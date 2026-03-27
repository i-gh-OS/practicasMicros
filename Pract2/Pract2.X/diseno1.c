/* 
 * File:   diseno1.c
 * Author: laboratorios
 *
 * Created on 30 de enero de 2026, 17:41
 */

#include <xc.h>

int main(void) {
  
    TRISC = 0xFFF0;
   // LATC = 0xFFFE;
    
    LATC = 0xFFF5;
    
    while (1)
        ;
    return 0;
    
}

