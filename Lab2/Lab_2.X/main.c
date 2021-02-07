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
#define _XTAL_FREQ (8000000)

//******************************************************************************
//Variables
//******************************************************************************

int ADC_value;
int Debounce_counter_b1 = 0;

//******************************************************************************
//Llamo Funciones
//******************************************************************************

void conf_timer0(void);
void conf_but(void);

//******************************************************************************
//Ciclo Principal
//******************************************************************************

void main(void) {
    //conf_timer0();
    conf_but();
    confADC();
    while(1){ //Main Loop
        __delay_ms(10); // Acquisition time
        ADCON0bits.GO = 1; // Enciende la conversion
        while (ADCON0bits.GO_nDONE){ //Hasta que no apague no sale
        }
        ADC_value = ADRESH; //Cuando acaba copia el valor del adresh en var ADC
        PORTC = ADC_value; // Copio lo del puerto al ADC
        
    }
}


//******************************************************************************
//Funciones
//******************************************************************************

void conf_timer0(void){ 
    // CONFIGURO MI INTERRUPCION DE TIMER0
    INTCONbits.TMR0IE =1; //Habilito el timer0
    OPTION_REGbits.PSA = 0; //Este bit puede habilitar al WDT o al T0(ahorita)
    OPTION_REGbits.T0CS = 0; //Si tenemos cristal interno o externo, toma el int
    OPTION_REGbits.INTEDG = 1; // flanco subida o bajada, este bajada
    OPTION_REGbits.PS0 = 0;
    OPTION_REGbits.PS1 = 0; // Set prescaler a 1:32 sin precarga 4ms por int
    OPTION_REGbits.PS2 = 1;
    TMR0 = 0; 
    // TERMINA CONFIG TIMER0  
}

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
    
    
}

//******************************************************************************
//Codigo de interrupcion
//******************************************************************************
void __interrupt() ISR(void){//Interrupcion
    if(INTCONbits.RBIF == 1){ // Si la bandera esta activada entre al if
        if(PORTBbits.RB1 == 1){ 
            PORTD++;//Si el boton en pull up == 0, presionado, entre
        }
        else if (PORTBbits.RB0 == 1){
            PORTD--;
        }
        INTCONbits.RBIF = 0;//Apaga bandera al contar 1 o al no entrar
        }
    }



