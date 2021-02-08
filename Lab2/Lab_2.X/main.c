/*
 * File:   main.c
 * Author: Larry Paul Fuentes
 * Carné: 18117
 *
 * Created on 5 de febrero de 2021, 10:24 PM
 */
//******************************************************************************
//Librerias
//******************************************************************************
// CONFIG1

#pragma config FOSC = HS// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
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
#pragma    config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include "Adc_int_.h"
#include "7_Segments.h"
#define Multiplex1 RE0
#define Multiplex2 RE1
#define _XTAL_FREQ (8000000)

//******************************************************************************
//Variables
//******************************************************************************

int adc_fin;
unsigned char Actual = 0;
unsigned char Num[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
//******************************************************************************
//Llamo Funciones
//******************************************************************************

void conf_but(void);

//******************************************************************************
//Ciclo Principal
//******************************************************************************

void main(void) {
    //conf_timer0();
    conf_but();
    confADC();
    adc_fin = 0;
    Multiplex1 = Multiplex2 = 0;
    conf_timer0();
    unsigned int x=0;
    while(1){ //Main Loop
        if (adc_fin == 0){ // Entra una vez se haya terminado de copiar el ADC
        __delay_ms(10); // Acquisition time
        ADCON0bits.GO = 1; // Enciende la conversion
        adc_fin = 1; //Bandera para comprobar si ya se copio la conversion.
        }
        __delay_ms(20);
        change(x++);
    }
}


//******************************************************************************
//Funciones
//******************************************************************************



void conf_but(void){
    // CONFIGURACION PUERTOS
    INTCONbits.GIE = 1; //Habilito mis interrupciones
    INTCONbits.PEIE = 1; //Habilita interrupciones perifericas
    INTCONbits.RBIE = 1; 
    ANSEL = 0;// Indicar que el ansel y el anselh esten en 0, (digirales)
    ANSELH = 0;
    ANSELbits.ANS0 = 1; //Excepto el pin AN0 (Pot)
    TRISC=0x00; 
    TRISB=0x00; //Pone los puertos como outputs, en b los prim 2 pin input
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1; //Habilitar los puertos como entradas
    IOCB = 0b00000011; //Indicar que pines estan 
    TRISD=0x00;
    TRISE=0x00;
    TRISA=0;
    TRISAbits.TRISA0 = 1;//habilita como entrada el puerto analogico (pot)
    PORTD = 0;
    PORTB = 0;
    PORTC = 0;
    PORTE = 0;
    
    
}

//******************************************************************************
//Codigo de interrupcion
//******************************************************************************
void __interrupt() ISR(void){//Interrupciones
    if(INTCONbits.RBIF == 1){ // Si la bandera del interrupt on change "if"
        if(PORTBbits.RB1 == 1){ 
            PORTD++;//Si el boton esta presionado, aumenta el puerto
        }
        else if (PORTBbits.RB0 == 1){
            PORTD--; // Si el boton esta presionado, decrementa
        }
        INTCONbits.RBIF = 0;//Apaga bandera al terminar la accion.
        }

    if(PIR1bits.ADIF == 1){ //Chequea la bandera del ADC
        PORTC = ADRESH; //Copia el valor de la conversion al puerto C
        adc_fin = 0; //Apagar bandera de copiando conversion
        PIR1bits.ADIF = 0;   //Apagar bandera de conversion
    }
    if(T0IF){
        if(Actual==0) 
    {
      PORTC = 0x00;
      Multiplex1 = 1;
      Multiplex2 = 0;
      PORTC = Num[Pos[0]];
    }
    if(Actual==1)
    {
      PORTC = 0x00;
      Multiplex2 = 1;
      Multiplex1 = 0;
      PORTC = Num[Pos[1]];
    }
    Actual++;
    if(Actual==2){
    Actual=0;
    T0IF = 0;
    TMR0 = 0; // Preloading Timer1
  }
    }
    }



