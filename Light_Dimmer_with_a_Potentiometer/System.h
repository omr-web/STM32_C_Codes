/*
 * System.h
 *
 *  Created on: 6 Ocak 2021
 *      Author: ÖMER Cebeci
 */

#ifndef MODULS_SYSTEM_H_
#define MODULS_SYSTEM_H_


void System_Init();

void System_Segment_Init();


void ADC_Init();


void print(char *buf);
void printchar(uint8_t c);
uint16_t ADC_Data();


//void System_Timer3_Init();

void System_Timer14_Init();
void UART_Init(uint32_t);
void System_Analog_LED_Init();
void LED_Init();


void Delay(volatile uint32_t);







#endif /* MODULS_SYSTEM_H_ */
