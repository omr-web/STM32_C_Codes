/*
 * System.h
 *
 *  Created on: 5 Ara 2020
 *      Author: ÖMER
 */

#ifndef MODULS_SYSTEM_H_
#define MODULS_SYSTEM_H_


void System_Init();

void System_Segment_Init();






void System_Timer_Init();



void System_Alternate_LED_Init();
void System_LED_Toggle();
void System_LED_Set();
void System_LED_Reset();

void Delay(volatile uint32_t);
void System_Button_Init();
int System_Button_read();






#endif /* MODULS_SYSTEM_H_ */
