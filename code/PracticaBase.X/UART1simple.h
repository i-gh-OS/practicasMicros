/* 
 * File:   UART1.h
 * Author: DEAC
 *
 * Created on 2 de marzo de 2018, 11:39
 */

#ifndef UART1_H
#define	UART1_H

#ifdef	__cplusplus
extern "C" {
#endif

void InicializarUART1(int baudios);

 /**
 * Extrae un carácter de la cola de recepción y lo devuelve. Si la cola
 * está vacía devuelve un \0.
 *
 * @return  caracter extraído de la cola
 */
char getcUART(void);

  /**
 * Envía un carácter a la UART1 y habilita el transmisor para que se envíe
 * 
 * @param c carácter a enviar
 */
void putcUART(char c);
  
  /**
 * Envia una cadena de caracteres a la cola de transmisión y habilita
 * el transmisor para que se envíe
 * 
 * @param s cadena de caracteres a enviar
 */
void putsUART(char *ps);


#ifdef	__cplusplus
}
#endif

#endif	/* UART1_H */

