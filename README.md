<center>![logo](http://png-5.vector.me/files/images/7/5/75754/utep_miners_thumb.png)</center>

#**UTEP Electrical Engineering**

###**MSPIO**
***
A UART printf and gets for the MSP432, inspired by the popular [MSP430 Printf](http://www.msp430launchpad.com/2012/06/using-printf.html)
***

###**Project Setup**
***
In order to use the project you will need to have the [MSP432 SimpleLink SDK](http://www.ti.com/tool/SIMPLELINK-MSP432-SDK) library installed. To install it follow the link and select the SIMPLELINK-MSP432-SDK option, after the installation is complete import this project into Code Composer's Workspace. 

The UARTIO Card project is divided into a folder and two source files:

- **Hardware**: This folder contains all hardware peripheral code (UART_Driver)
- **MSPIO.c**: The source file contains the functions for UARTIO
-  **MSPIO.h**: The header file contains all UARTIO definitions

***

### **How to use it**
***
First of all, you have to include the following header files 
```c
#include <Hardware/CS_Driver>
#include "MSPIO.h"
```
After that, declare the UART configuration structure variable as follows:
```c
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
```

Then initialize the UART and Clock hardware:
```c
#include <Hardware/CS_Driver.h>
#include "MSPIO.h"

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

void main()
{
	WDT_A_holdTimer();
	
	/*24 MHz clock, you might want to try different clock rates*/
	CS_Init()
	
	/*Initialize the desired UART peripheral, in this example we use UART A0.
	Pass the initialized UART configuration structure variable*/
	UART_Init(EUSCI_A0_BASE, UART0Config)
}
```
To use MSPrintf you need to pass the formatted string as you would if you were using the c standard printf.  **DON'T** forget to initialize the desired UART before using this function
```c
char c = 'c';
char str[] = "Hello World";
int integer = 1234;

MSPrintf(EUSCI_A0_BASE, "This is a formatted string %c, %s, %i", character, str, integer);
```
MSPgets will wait for user input. This function will not return until the user sends a '\r' or '\n' character. After the user sends one of those two characters, the received string will be saved on the buffer that was passed to MSPgets **DON'T** forget to initialize the desired UART before using this function
```c
char Buffer[128];
/*Wait for user input*/
MSPgets(EUSCI_A0_BASE, Buffer, sizeof(Buffer));

/*if we are here that means the user sent a '\r' or '\n' character, the received string will be stored in the Buffer array*/
```
***
### **Other Details and Future Work**
***
If you are using the MSP432 PC UART, you will need to initialize UART A0. Then open up your preferred serial terminal and enter the COM port. If you do not know the COM port of the MSP432 follow this [guide](https://www.mathworks.com/help/supportpkg/arduinoio/ug/find-arduino-port-on-windows-mac-and-linux.html).

To send information to the MSP432 just type characters into the serial console (you need to call MSPgets to store the received string). The MSP432 will echo all received characters. If you wish to disable this, go to the UARTIO.c source file and comment out this line of code under the EUSCIA0_IRQHandler:
```c
 /*Transmit data only if it made it to the buffer*/
 MAP_UART_transmitData(EUSCI_A0_BASE, c);
```

I personally want to achieve a full Input/Output project, meaning that file handling must be added for this project. In a future iteration of this project I plan to include a file system so that the Input/Output will be completed. If you 