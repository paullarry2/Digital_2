/* 
 * File:   Adc_int.h
 * Author: Larry Paúl Fuentes
 * Carné 18117
 * Digital 2
 * Lab2
 * Created on 7 de febrero de 2021, 01:19 PM
 */

#ifndef __7_SEGMENTS_
#define	__7_SEGMENTS_

#include <xc.h>
#include <stdint.h>


unsigned char Pos[2] = {5, 3};
//******************************************************************************
//Llamo Funciones
//******************************************************************************
void conf_timer0(void);
void change(unsigned int nu);


#endif	/* XC_HEADER_TEMPLATE_H */

