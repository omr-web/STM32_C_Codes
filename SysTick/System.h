/*
 * System.h
 *
 *  Created on: 5 Ara 2020
 *      Author: ÖMER
 */

#ifndef MODULS_SYSTEM_H_
#define MODULS_SYSTEM_H_


void System_Init();

void System_LED_Init();
void System_LED_Toggle();
void System_LED_Set();
void System_LED_Reset();


void System_Button_Init();
int System_Button_read();



void SysTick_Handler();
void Delay_ms(uint32_t);

#endif /* MODULS_SYSTEM_H_ */
