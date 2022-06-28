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

uint8_t ReadI2C (uint8_t, uint8_t);
void Init_I2C (void);
void write_I2C(uint8_t, uint8_t,uint8_t);
void Multi_ReadI2C (uint8_t, uint8_t,uint8_t*,uint32_t);

void Multi_Write(uint8_t, uint8_t*, uint32_t);



void UART_Init(uint32_t);
void printchar(uint8_t);
void print2(int,char* ,int);
void print(char *);
uint8_t uart_rx(void); // UART receive data
void uart_tx (uint8_t); // UART transmit data






#endif /* MODULS_SYSTEM_H_ */
