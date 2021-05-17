// Larry Paúl Fuentes
// Carné 18117
// Digital 2
// Laboratorio 6
// 14/05/2021

#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/tm4c123gh6pm.h"
#include"driverlib/sysctl.h"
#include"driverlib/gpio.h"
#include"driverlib/timer.h"
#include"driverlib/interrupt.h"
#include "driverlib/uart.h"



/*******************************************************************
 *                      PROTOTIPO DE FUNCIONES
 * *****************************************************************/
 void Timer0IntHandler(void);
 void UARTIntHandler(void);



 /*******************************************************************
  *                      VARIABLES
  * *****************************************************************/
 int state = false;
 int rgb;
 int uart_f = false;
 int data;




 /*******************************************************************
  *                      MAIN LOOP
  * *****************************************************************/

int main(void)
{
    //RELOJ Y PUERTOS
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilitar los perifericos de La tiva C
    // Se utilizará la funcion del api para habilitar el puerto
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // Indico que usaremos el puerto F como salidas, y los pines 1 al 3.

    //TIMER0
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

    //UART
    // Habilitar los perifericos del UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // Habilitar perifercos A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Inicializamos los pines del UART
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
    // CONFIG 115200, 8 data bits, 1 stop bit, None parity. Usamos el uart0
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    // habilitamos la comunicación y el handler.
    UARTIntEnable(UART0_BASE, UART_INT_RT | UART_INT_RX);
    UARTIntRegister(UART0_BASE, UARTIntHandler);


    while(1){
        if (state && uart_f == 1){
            // Si ambas banderas estan habilitadas, es decir se quiere imprimir un color y la interrupcion lo indica, se prende
            // el led de la tiva, con el color indicado por UART
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, rgb);
        }
        else{ // En el caso contrario apagado.
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);
        }
    }


}

/*******************************************************************
 *                      FUNCIONES
 * *****************************************************************/

void Timer0IntHandler(void){
    TimerIntClear(TIMER0_BASE, TIMER_A); //Borro el timer.
    state = !state; // toggle bandera estado

}

void UARTIntHandler(void){
    UARTIntClear(UART0_BASE, UART_INT_RT | UART_INT_RX);
    data = UARTCharGet(UART0_BASE); // Lee el puerto UART, y lo almacena en data.
    if (data == 'r'){
        uart_f = !uart_f; // Bandera uart_f, me indica cuando quiere ser habilitado el toggle.
        rgb = 2; //Color Rojo
    }
    else if (data == 'g'){
        uart_f = !uart_f;
        rgb = 8; // Color Verde
    }
    else if (data == 'b'){
        uart_f = !uart_f;
        rgb = 4; // Color Azul
    }
    else{
        uart_f = !uart_f;
        rgb = 10; // en caso de tener un valor erroneo en el puerto, se imprimira el toggle de color amarillo, indicando error
        UARTCharPut(UART0_BASE, 'E');
        UARTCharPut(UART0_BASE, 'r');
        UARTCharPut(UART0_BASE, 'r');
        UARTCharPut(UART0_BASE, 'o');
        UARTCharPut(UART0_BASE, 'r');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'i');
        UARTCharPut(UART0_BASE, 'n');
        UARTCharPut(UART0_BASE, 't');
        UARTCharPut(UART0_BASE, 'e');
        UARTCharPut(UART0_BASE, 'n');
        UARTCharPut(UART0_BASE, 't');
        UARTCharPut(UART0_BASE, 'e');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'o');
        UARTCharPut(UART0_BASE, 't');
        UARTCharPut(UART0_BASE, 'r');
        UARTCharPut(UART0_BASE, 'a');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'v');
        UARTCharPut(UART0_BASE, 'e');
        UARTCharPut(UART0_BASE, 'z');
        UARTCharPut(UART0_BASE, 10);
        UARTCharPut(UART0_BASE, 13);
    }
}

