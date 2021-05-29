// Larry Paul Fuentes
// Proyecto Parqueo
// 28/05/2021
// Digital 2

#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"inc/tm4c123gh6pm.h"
#include"driverlib/sysctl.h"
#include"driverlib/gpio.h"
#include"driverlib/timer.h"
#include"driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"



int main(void)
{
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    //Peripheral Enable
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    //LEDS
    GPIOPinConfigure(GPIO_PD0_WT2CCP0); //D0
    GPIOPinConfigure(GPIO_PD1_WT2CCP1); //D1

    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5| GPIO_PIN_6 | GPIO_PIN_7); //A
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5| GPIO_PIN_6); //B
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1); //D
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4); //Pushes E

    //Luces inciales
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0| GPIO_PIN_1, GPIO_PIN_0); //D0
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5| GPIO_PIN_6 | GPIO_PIN_7,
                 GPIO_PIN_2| GPIO_PIN_4 | GPIO_PIN_6); //A2,4,6
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_1);// D1
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5| GPIO_PIN_6 | GPIO_PIN_7,
                 GPIO_PIN_3| GPIO_PIN_5 | GPIO_PIN_7); //A3,5,7

    while (1)
       {

       }


}
