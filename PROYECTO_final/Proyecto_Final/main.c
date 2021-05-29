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

int p1;
int p2;
int p3;
int p4;
int disp = 0;
int d1;
int d2;
int d3;
int d4;

//Prototipo de funciones
void Revision(void);
void display(void);

// Display
//-----------
// PB0 - g
// PB1 - f
// PB2 - a
// PB3 - b
// PB4 - e
// PB5 - d
// PB6 - c

// Leds
//------------
// PD0
// PD1
// PA2 - PA7

//Pushes
//------------
// PE1
// PE2
// PE3
// PE4

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

    //PUSH BUTTONS
 //   GPIOPinConfigure(GPIO_PE0_U7RX);    //1
   // GPIOPinConfigure(GPIO_PE1_U7TX);    //2
    //GPIOPinConfigure(GPIO_PE4_U5RX);    //3
    //GPIOPinConfigure(GPIO_PC4_WT0CCP0);   //4

    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5| GPIO_PIN_6 | GPIO_PIN_7); //
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5| GPIO_PIN_6); //Display Output
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1); //D
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4); //Pushes E

    //Pullups
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);


    //Luces inciales
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0| GPIO_PIN_1, GPIO_PIN_0); //D0
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5| GPIO_PIN_6 | GPIO_PIN_7,
                 GPIO_PIN_2| GPIO_PIN_4 | GPIO_PIN_6); //A2,4,6
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_1);// D1
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5| GPIO_PIN_6 | GPIO_PIN_7,
                 GPIO_PIN_3| GPIO_PIN_5 | GPIO_PIN_7); //A3,5,7

    while (1)
       {

        //Leer pushes
        p1 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1);
        p2 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2);
        p3 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3);
        p4 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4);
        disp = d1 + d2 +d3 + d4; // Contador de Display
        Revision(); // Revisa los estados de los botones
        display(); // Display

       }
}

void Revision(void)
{
    if (p1 == 0)
    { //Parqueo 1 esta ocupado se enciende led roja
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
        d1 = 0; // La badera se apaga ya que tendran un espacio disponible menos
    }
    else
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
        d1 = 1;
    }

    if (p2 == 0)
    { //Parqueo 2 esta ocupado se enciende led roja
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);
        d2 = 0;
    }
    else
    {
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);
        d2 = 1;
    }

    if (p3 == 0)
        { //Parqueo 2 esta ocupado se enciende led roja
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0);
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4);
            d3 = 0;
        }
        else
        {
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
            d3 = 1;

        }
    if (p4 == 0)
        { //Parqueo 2 esta ocupado se enciende led roja
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
            d4 = 0;
        }
        else
        {
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);
            d4 = 1;
        }
}

void display(void){

    // Display
    //-----------
    // PB0 - g
    // PB1 - f
    // PB2 - a
    // PB3 - b
    // PB4 - e
    // PB5 - d
    // PB6 - c
    // Switch Case normal con todos los numeros.
    switch (disp){
    case 0:

    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0| GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 ,  GPIO_PIN_0); //0
    break;
    case 1:
    // 0,1,2,4,5
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0| GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 ,
                 GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5); //1
    break;
    case 2:
    //1,6
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0| GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 ,
                GPIO_PIN_1|GPIO_PIN_6); //2
    break;
    case 3:
    //1,4
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0| GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 ,
                 GPIO_PIN_1|GPIO_PIN_4); //3
    break;
    case 4:
    //2,4,5

    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0| GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 ,
                  GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5); //4
    break;
}
}

