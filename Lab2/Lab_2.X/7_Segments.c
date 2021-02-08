#include "7_Segments.h"

void conf_timer0() {
    // CONFIGURO MI INTERRUPCION DE TIMER0
    INTCONbits.TMR0IE = 1; //Habilito el timer0
    OPTION_REGbits.PSA = 0; //Este bit puede habilitar al WDT o al T0(ahorita)
    OPTION_REGbits.T0CS = 0; //Si tenemos cristal interno o externo, toma el int
    OPTION_REGbits.INTEDG = 1; // flanco subida o bajada, este bajada
    OPTION_REGbits.PS0 = 0;
    OPTION_REGbits.PS1 = 0; // Set prescaler a 1:32 sin precarga 4ms por int
    OPTION_REGbits.PS2 = 1;
    TMR0 = 0;
    // TERMINA CONFIG TIMER0  
}

void change(unsigned int nu) {
    if (nu <= 99) {
        Pos[0] = nu / 10;
        nu %= 10;
        Pos[1] = nu;
    }
}
