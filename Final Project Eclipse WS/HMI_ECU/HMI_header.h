/*
 * File: HMI_header.h
 * Description: header file for HMI_ECU
 * Author: Shahd Mohamed
 */

#ifndef HMI_HEADER_H_
#define HMI_HEADER_H_

#include "keypad.h"
#include "lcd.h"
#include "timer1.h"
#include "uart.h"
#include "avr/interrupt.h"
#include "gpio.h"
#include<util/delay.h>

/*******************************************************************************
 *                            Definition                                       *
 *******************************************************************************/

#define WRONG_PASS                  0
#define SETTING_NEW_PASSWORD        1
#define READY_TO_COMMUNICATE        2
#define STEP_3_OPEN_DOOR            3
#define STEP_4_CHANGE_PASS          4
#define MATCH                       5
#define NOT_MATCHING                6

#define PASSWORD_SIZE               5

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description:
 *	Function to get the new password and send it to control EUC
 * */
void HMI_settingNewPassword(void);


/*
 * Description:
 *	  Function to get the password from the user and send it to control EUC
 * */
uint8 HMI_getPassword(void);


/*
 * Description:
 *	  Function to choose from the main options
 *	  + : open the door.
 *	  - : Change password.
 *	  and send it to CONTROL ECU
 * */
uint8 HMI_mainOptions(void);


/*
 * Description:
 * Function to set stop_buzzer after to delete error message on LCD
 * after 1 minute from displaying it
 */
void HMI_errorLCDProcessing(void);

/*
 * Description:
 * call back function of timer1, to control LCD while opening and closing the door
 */
void Controling_LCD_openDoorState (void);
#endif
