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
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>

//******************************************************************************
//Variables
//******************************************************************************

int Debounce_counter_b0 = 0;
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
    conf_timer0();
    conf_but();
    while(1){
        if (Debounce_counter_b0 > 5){
            PORTD++;
            Debounce_counter_b0 = 0;
        }
        else if (Debounce_counter_b1 > 5){
            PORTD--;
            Debounce_counter_b1 = 0;
        }
}
}

//******************************************************************************
//Funciones
//******************************************************************************

void conf_timer0(void){ 
    // CONFIGURO MI INTERRUPCION DE TIMER0
    INTCONbits.GIE = 1; //Habilito mis interrupciones
    INTCONbits.TMR0IE =1; //Habilito el timer0
    OPTION_REGbits.PSA = 0; //Este bit puede habilitar al WDT o al T0(ahorita)
    OPTION_REGbits.T0CS = 0; //Si tenemos cristal interno o externo, toma el int
    OPTION_REGbits.INTEDG = 0; // flanco subida o bajada, este bajada
    OPTION_REGbits.PS0 = 0;
    OPTION_REGbits.PS1 = 0; // Set prescaler a 1:32 sin precarga 4ms por int
    OPTION_REGbits.PS2 = 1;
    TMR0 = 0; 
    // TERMINA CONFIG TIMER0  
}

void conf_but(void){
    // CONFIGURACION PUERTOS
    OPTION_REGbits.nRBPU = 1; //Habilita los pull up y latch individual de portb
    TRISC=0x00;
    TRISB=0b00000011; //Pone los puertos como outputs, en b los prim 2 pin input
    TRISD=0x00;
    TRISE=0x00;
    TRISAbits.TRISA0 = 1; //habilita como entrada el puerto analogico (pot)
    PORTD = 0;
    PORTB = 0;
    PORTC = 0;
    
    
}

//******************************************************************************
//Codigo de interrupcion
//******************************************************************************
void __interrupt() ISR(void){//Interrupcion
    if(INTCONbits.TMR0IF == 1){ // Si la bandera esta activada entre al if
        if(PORTBbits.RB1 == 0){ //Si el boton en pull up == 0, presionado, entre
            Debounce_counter_b1++; //Aumenta el contador antirebotes
        }
        else if (PORTBbits.RB0 == 0){
            Debounce_counter_b0++;
        }
        INTCONbits.TMR0IF = 0;    //Apaga bandera al contar 1 o al no entrar
        }
    }



