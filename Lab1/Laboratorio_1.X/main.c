/*
 * File:   main.c
 * Author: Larry Paul Fuentes
 * Carné: 18117
 *
 * Created on 29 de enero de 2021, 11:06 PM
 */
//******************************************************************************
//Librerias
//******************************************************************************
// CONFIG1
#pragma config FOSC = XT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
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
#define _XTAL_FREQ  8000000
#define Led_roja PORTEbits.RE0
#define Led_amarilla PORTEbits.RE1
#define Led_verde PORTEbits.RE2
#define Strt PORTBbits.RB0
#define Jugador_1 PORTBbits.RB1
#define Jugador_2 PORTBbits.RB2
#define Ganador_1 PORTAbits.RA1
#define Ganador_2 PORTAbits.RA0
#define J1 PORTC
#define J2 PORTD
int z;


//******************************************************************************
//Funciones
//******************************************************************************
void semaforo(void);
void setup(void);



//******************************************************************************
//Ciclo Principal 
//******************************************************************************

void main(void) {
    setup();

    while (1) {
        if (Strt == 1)
            semaforo();
        if ((Ganador_1 | Ganador_2) == 0 & Led_verde == 1) {
            if (J1 == 0 & Jugador_1 == 1) {
                __delay_ms(400);
                J1 = 0b0000001;
            } else if (Jugador_1 == 1 & J1 != 0) {
                __delay_ms(400);
                J1 = J1 << 1;
            }
            if (J2 == 0 & Jugador_2 == 1) {
                __delay_ms(400);
                J2 = 0b0000001;
            } else if (Jugador_2 == 1 & J2 != 0) {
                __delay_ms(400);
                J2 = J2 << 1;
            }
            if (PORTCbits.RC7==1){
                Ganador_1=1;
            }
            else if (PORTDbits.RD7==1){
                Ganador_2=1;
            }
        }
        

    }
}


//******************************************************************************
//Funciones
//******************************************************************************

void semaforo(void) {
    Led_roja = 1;
    __delay_ms(500);
    Led_roja = 0;
    Led_amarilla = 1;
    __delay_ms(500);
    Led_amarilla = 0;
    Led_verde = 1;
}

void setup(void) {
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    PORTA = 0;
    TRISB = 0b00000111;
    PORTB = 0;
    TRISC = 0;
    PORTC = 0;
    TRISD = 0;
    PORTD = 0;
    TRISE = 0;
    PORTE = 0;
}

