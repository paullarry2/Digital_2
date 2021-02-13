/*
 * File:   main.c
 * Author: Larry Paúl Fuentes
 * Carné 18117
 * Laboratorio 3
 * Digital 2
 *
 * Created on 11 de febrero de 2021, 08:32 PM
 */
//******************************************************************************
//Librerias
//******************************************************************************
#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
//#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma    config WRT = OFF 

#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "Adc_int_.h"
#include "lcd.h"

#define _XTAL_FREQ (8000000)

//******************************************************************************
//Variables
//******************************************************************************
int pot;
uint8_t val_pot1;
uint8_t val_pot2;
int adc_fin = 0;
char buffer[64];
float voltaje;

//******************************************************************************
//Prototipo de funciones
//******************************************************************************
void config(void);

//******************************************************************************
//Main Loop
//******************************************************************************

void main(void) {
    config();
    confADC();
    adc_fin = 0;
    Lcd_Init();
    Lcd_Clear();
    while (1) {
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("S1:");
        Lcd_Set_Cursor(1,8);
        Lcd_Write_String("S2:");
        Lcd_Set_Cursor(1,13);
        Lcd_Write_String("S3:");
        
        if (adc_fin == 0) {
            adc_fin = 1; //Bandera para comprobar si ya se copio la conversion.
            if (pot == 0) {
                conf_ch(0); //COnfigura canal 0 RA0
                __delay_ms(10); // Acquisition time
                ADCON0bits.GO = 1; // Enciende la conversion

            }
            if (pot == 1) {
                conf_ch(1); //Configura canal 1 RA1
                __delay_ms(10); // Acquisition time
                ADCON0bits.GO = 1; // Enciende la conversion
            }
        }
        
    }
}
//******************************************************************************
//Funciones
//******************************************************************************

void config(void) {
    // CONFIGURACION PUERTOS
    INTCONbits.GIE = 1; //Habilito mis interrupciones
    INTCONbits.PEIE = 1; //Habilita interrupciones perifericas
    ANSEL = 0; // Indicar que el ansel y el anselh esten en 0, (digirales)
    ANSELH = 0;
    ANSELbits.ANS0 = 1; //Excepto el pin AN0 (Pot)
    ANSELbits.ANS1 = 1;
    TRISC = 0x00;
    TRISB = 0x00; //Pone los puertos como outputs, en b los prim 2 pin input
    TRISD = 0x00;
    TRISE = 0x00;
    TRISA = 0;
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1; //habilita como entrada el puerto analogico (pot)
    PORTD = 0;
    PORTB = 0;
    PORTC = 0;
    PORTE = 0;
    pot = 0;

}

//******************************************************************************
// Interrupcion
//******************************************************************************

void __interrupt() ISR(void) {//Interrupciones

    if (PIR1bits.ADIF == 1) {
        if (pot == 0) {//Chequea la bandera del ADC
            val_pot1 = ADRESH; //Copia el valor de la conversion al puerto C
            adc_fin = 0; //Apagar bandera de copiando 
            pot = 1;
            voltaje = (val_pot1 * 5.0) / 255;
            Lcd_Set_Cursor(2, 1);
            sprintf(buffer, "%.2f", voltaje);
            Lcd_Write_String(buffer);
            
        }
        else if (pot == 1) {
            val_pot2 = ADRESH; //Copia el valor de la conversion al puerto C
            adc_fin = 0; //Apagar bandera de copiando conversion
            pot = 0;
            voltaje = (val_pot2 * 5.0) / 255;
            Lcd_Set_Cursor(2, 1);
            sprintf(buffer, "%.2f", voltaje);
            Lcd_Write_String(buffer);
        }
    }
    PIR1bits.ADIF = 0; //Apagar bandera de conversion
}