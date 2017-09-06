#include <Hardware/CS_Driver.h>
#include "MSPIO.h"

/*Input Buffer*/
char Buffer[128];

/* UART Configuration Parameter. These are the configuration parameters to
 * make the eUSCI A UART module to operate with a 115200 baud rate. These
 * values were calculated using the online calculator that TI provides
 * at:
 * http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 */
eUSCI_UART_Config UART0Config =
{
     EUSCI_A_UART_CLOCKSOURCE_SMCLK,
     13,
     0,
     37,
     EUSCI_A_UART_NO_PARITY,
     EUSCI_A_UART_LSB_FIRST,
     EUSCI_A_UART_ONE_STOP_BIT,
     EUSCI_A_UART_MODE,
     EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
};

void main(void)
{
    /*Initialize the clock to 24MHz*/
    CS_Init();
    /*Initialize UARTA0 (PC UART) using the UART0config structure variable*/
    UART_Init(EUSCI_A0_BASE, UART0Config);

    /*Test variables*/
    char c = 'c';
    char s[] = "Hello";
    int i = 1234;

    /*Print formated string*/
    MSPrintf(EUSCI_A0_BASE, "Formated string %c %s %i", c, s, i);

    while(1)
    {
        /*wait for user input*/
        MSPgets(EUSCI_A0_BASE, Buffer, 128);
        /*Echo user input*/
        MSPrintf(EUSCI_A0_BASE, "Received: %s\r\n", Buffer);
    }
}
