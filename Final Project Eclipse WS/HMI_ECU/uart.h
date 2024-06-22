 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                      Types Declarations                                     *
 *******************************************************************************/
typedef enum
{
  FIVE_BIT_FRAME, SIX_BIT_FRAME, SEVEN_BIT_FRAME, EIGHT_BIT_FRAME, NINE_BIT_FRAME=7
}UART_BitData;

typedef enum
{
	DISABLE_PARITY, ENABLE_EVEN_PARITY=2, ENABLE_ODD_PARITY
}UART_Parity;

typedef enum
{
    ONE_STOP_BIT, TWO_STOP_BITS
}UART_StopBit;

typedef uint16 UART_BaudRate;


typedef struct{
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 UART_BaudRate baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

/*******************************************************************************
 *                      Extern Declarations                                    *
 *******************************************************************************/
extern UART_ConfigType UART_Config;

#endif /* UART_H_ */
