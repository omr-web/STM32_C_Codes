/*
 * System.h
 *
 *  Created on: 6 Ocak 2021
 *      Author: ÖMER Cebeci
 */
#ifndef MODULS_SYSTEM_H_
#define MODULS_SYSTEM_H_
int counter;
void System_Button_Init();
int System_Button_read();
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
void Number_Find(uint32_t);
void Display_Number(int);
void System_D1();
void System_D2();
void System_D3();
void System_D4();
void System_Init();
void System_Segment_Init();
void ADC_Init();
void print(char *buf);
void printchar(uint8_t c);
uint16_t ADC_Data();
void System_Timer14_Init();
void UART_Init(uint32_t);
void LED_Init();
void Delay(volatile uint32_t);
#endif /* MODULS_SYSTEM_H_ */
