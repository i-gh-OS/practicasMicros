/* 
 * File:   main.c
 * Author: irene
 *
 * Created on January 23, 2026, 6:04 PM
 */
#include <xc.h>

int main(void) {
  
    TRISC = 0xFFF0;
    LATC = 0xFFF0;
    while (1)
        ;
    return 0;
}
