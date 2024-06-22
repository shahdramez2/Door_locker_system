/*
 * File: HMI_fucntions.c
 * Description: source file for function Definitions of HMI_ECU application
 * Author: Shahd Mohamed
 */

#include "HMI_header.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

volatile uint16 g_tick = 0;
volatile uint8 open_flag = 0;
volatile uint8 stop_flag=0;
volatile uint8 CloseDoorFlag = 0;
volatile uint8 close_flag = 0;
volatile uint8 stop_buzzer = 0;

/*******************************************************************************
 *                      Functions Definition                                   *
 *******************************************************************************/
/*
 * Description:
 *	Function to get the new password and send it to control EUC
 * */
void HMI_settingNewPassword(void)
{
	uint8 NewPassword[PASSWORD_SIZE + 2];
	uint8 check_password[PASSWORD_SIZE + 2];
	uint8 index;
	uint8 enter_key; /*variable used to get enter key*/
	//	uint8 errorConfirm = 0;

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0, "plz enter pass:");
	LCD_moveCursor(1,0); /* second row for password */

	for(index = 0; index<PASSWORD_SIZE; index++)
	{
		NewPassword[index] = KEYPAD_getPressedKey();
		_delay_ms(500);

		if((NewPassword[index] >= 0) && (NewPassword[index] <= 9))
		{
			if(NewPassword[index] == 0)
			{
				/* replace zero by -1 to not be considered as null*/
				NewPassword[index] = -1;
			}

			LCD_displayString("*");

		}
	}

	/* waiting until user presses '=' which represents enter */
	while(1)
	{
		enter_key= KEYPAD_getPressedKey();
		_delay_ms(500);
		if(enter_key == '=')
		{
			break;
		}
	}
	NewPassword[index] = '#';
	index++;
	NewPassword[index] = '\0';

	UART_sendByte(READY_TO_COMMUNICATE);
	UART_sendString(NewPassword);


	LCD_clearScreen(); /* clear screen to display new content */

	/* ask the user to enter the same password again */
	LCD_displayStringRowColumn(0,0, "plz re-enter the");
	LCD_displayStringRowColumn(1,0,"same pass:");

	for(index = 0; index<PASSWORD_SIZE; index++)
	{
		check_password[index] = KEYPAD_getPressedKey();
		_delay_ms(500);
		/* replace zero by -1 to avoid conflict with null*/
		if(check_password[index] == 0)
		{
			check_password[index] = -1;
		}
		LCD_displayString("*");
	}

	/* waiting until user presses '=' which represents enter */
	while(1)
	{
		enter_key= KEYPAD_getPressedKey();
		_delay_ms(500);
		if(enter_key == '=')
		{
			break;
		}
	}

	check_password[index] = '#';
	index++;
	check_password[index] = '\0';

	UART_sendByte(READY_TO_COMMUNICATE);
	UART_sendString(check_password);
}


/*
 * Description:
 *	  Function to get the password from the user and send it to control EUC
 * */
uint8 HMI_getPassword(void)
{
	uint8 password[PASSWORD_SIZE+2];
	uint8 index;
	uint8 enter_key; /*variable used to get enter key*/

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Plz enter pass:");
	LCD_moveCursor(1,0);

	for(index = 0; index<PASSWORD_SIZE; index++)
	{
		/* replace zero by -1 to avoid conflict with null*/
		password[index] = KEYPAD_getPressedKey();
		_delay_ms(500);

		/* replace zero by -1 to not be considered as null*/
		if(password[index] == 0)
		{
			password[index] = -1;
		}
		LCD_displayString("*");
	}

	/* waiting until user presses '=' which represents enter */
	while(1)
	{
		enter_key= KEYPAD_getPressedKey();
		_delay_ms(500);
		if(enter_key == '=')
		{
			break;
		}
	}
	password[index] = '#';
	index++;
	password[index] = '\0';

	UART_sendByte(READY_TO_COMMUNICATE);
	UART_sendString(password);

	UART_sendByte(READY_TO_COMMUNICATE);
	return UART_receiveByte();
}


/*
 * Description:
 *	  Function that indicate if the entered password and the stored password
 *	  are matched or not
 * */
uint8 HMI_matchPass(void)
{
	UART_sendByte(READY_TO_COMMUNICATE);

	return UART_receiveByte();
}


/*
 * Description:
 *	  Function to choose from the main options
 *	  + : open the door.
 *	  - : Change password.
 *	  and send it to CONTROL ECU
 * */
uint8 HMI_mainOptions(void)
{
	uint8 key_option;
	do
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "+: Open Door");
		LCD_displayStringRowColumn(1, 0, "-: Change Pass");

		key_option = KEYPAD_getPressedKey();
		_delay_ms(500);

		if(key_option == '+')
		{
			/*start communication with Control_ECU*/
			UART_sendByte(READY_TO_COMMUNICATE);
			UART_sendByte(STEP_3_OPEN_DOOR);
			return STEP_3_OPEN_DOOR;
		}
		else if(key_option == '-')
		{
			/*start communication with Control_ECU*/
			UART_sendByte(READY_TO_COMMUNICATE);
			UART_sendByte(STEP_4_CHANGE_PASS);
			return STEP_4_CHANGE_PASS;
		}
		else
		{
			/* handling case if input isn't '+' or '-" */
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Invalid Input");
			LCD_displayStringRowColumn(1, 0, "Enter + OR -");
		}
	}while(1);

}


/*
 * Description:
 * call back function of timer1, to control LCD while opening and closing the door
 */
void Controling_LCD_openDoorState (void)
{

	static uint8 timer1_tick=0;
	timer1_tick++;

	if(timer1_tick == 5)
	{
		/* stop displaying open door message */
		open_flag=1;

	}
	else if(timer1_tick==6)
	{
		stop_flag=1;
	}
	else if(timer1_tick == 11 )
	{
		/* stop displaying open door message */
		close_flag =1;

		/* put zero in timer1_tick to start same calculations when opening door again*/
		timer1_tick=0;
	}
}


/*
 * Description:
 * Function to set stop_buzzer after to delete error message on LCD
 * after 1 minute from displaying it
 */
void HMI_errorLCDProcessing(void)
{
	stop_buzzer=1;
}



