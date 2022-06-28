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


void System_Number1();
void System_Number2();
void System_Number3();
void System_Number4();
void System_Number5();
void System_Number6();
void System_Number7();
void System_Number8();
void System_Number9();
void System_Number0();

void System_D_Reset();
void System_D1();
void System_D2();
void System_D3();
void System_D4();

void System_Timer_Init();
void Number_Find(uint32_t);
void Display_Number(int);

void Normal_Mode();
void Display_zero();

void System_LED_Init();
void System_LED_Toggle();
void System_LED_Set();
void System_LED_Reset();

void Delay(volatile uint32_t);
void System_Button_Init();
int System_Button_read();


void Update_WatchDog();



#endif /* MODULS_SYSTEM_H_ */
