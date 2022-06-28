/*
 * System.h
 *
 *  Created on: 5 Ara 2020
 *      Author: ÖMER
 */

#ifndef MODULS_SYSTEM_H_
#define MODULS_SYSTEM_H_


void System_Init();


void System_Timer_Init();//for pwm signal
void UART_Init(uint32_t);  // for print duty cycle


void System_Alternate_LED_Init(void);  // for pwm signal



void Delay(volatile uint32_t);
void System_Keypad_Button_Init(void); // for keypad initialize
void System_Keypad_Output_Init(void);
void System_Keypad_Set(void);
void System_Keypad_Reset(void);


void printNumber(uint8_t);





#endif /* MODULS_SYSTEM_H_ */
