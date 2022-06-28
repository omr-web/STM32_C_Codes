/*
 * System.h
 *
 *  Created on: 5 Ara 2020
 *      Author: ÖMER
 */

#ifndef MODULS_SYSTEM_H_
#define MODULS_SYSTEM_H_

uint16_t i ;
void System_Init();
void System_Segment_Init();
void System_Timer_Init();
void System_Timer2_Init();
void System_Alternate_LED_Init();

void Delay(volatile uint32_t);

#endif /* MODULS_SYSTEM_H_ */
