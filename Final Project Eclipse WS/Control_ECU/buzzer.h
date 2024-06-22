/*
 * buzzer.h
 *
 *  Created on: Nov 1, 2022
 *      Author: SHAHD MOHAMED
 */

#ifndef BUZZER_H_
#define BUZZER_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID       PORTD_ID
#define BUZZER_PIN_ID        PIN7_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Function to initiate buzzer drive:
 * Setup the direction for the buzzer pin as output pin through the GPIO driver
 * Turn off the buzzer through the GPIO.
 */
void Buzzer_init(void);


/*
 * Description:
 * Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void);


/*
 * Description:
 * Function to disable the Buzzer through the GPIO.
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */