// Larry Paúl Fuentes
// Carné 18117
// Digital 2
// Laboratorio 6
// 14/05/2021

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"



/*******************************************************************
 *                      PROTOTIPO DE FUNCIONES
 * *****************************************************************/
 void Timer0IntHandler(void);


 /*******************************************************************
  *                      VARIABLES
  * *****************************************************************/
 int state = false;
 int rgb;




 /*******************************************************************
  *                      MAIN LOOP
  * *****************************************************************/

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilitar los perifericos de La tiva C
    // Se utilizará la funcion del api para habilitar el puerto
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // Indico que usaremos el puerto F como salidas, y los pines 1 al 3.
    // Ahora habilitamos los perifericos del Timer0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    // Configuracion de Timer0
    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC); // Habilitado como periodico de 32 bits.
    // El tiempo requerido es de 0.5s, por lo que al tener el reloj 40MHz, necesitamos un prescaler de 20M.
    TimerLoadSet(TIMER0_BASE, TIMER_A, 20000000); // Como es especificado el TimerA, debe de ser el unico utilizado ya que es FullWidth
    // Se habilita la interrupción por el TIMER0A
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
    IntEnable(INT_TIMER0A);
    // Se establece que exista la interrupción por Timeout
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    // Se habilitan las interrupciones Globales
    IntMasterEnable();
    // Se habilita el Timer
    TimerEnable(TIMER0_BASE, TIMER_A);

    while(1){
        if (state == 1){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 1);
        }
        else{
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
        }
    }


}

/*******************************************************************
 *                      FUNCIONES
 * *****************************************************************/

void Timer0IntHandler(void){
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); //Borro el timer.
    state = !state;

}
