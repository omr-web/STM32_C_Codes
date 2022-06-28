/*
 * SSD.h
 *
 *  Created on: 18 Ara 2020
 *      Author: ÖMER
 */

#ifndef SSD_H_
#define SSD_H_

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
void System_NumberA();
void System_NumberB();// -
void System_NumberAC();// C
void System_NumberD(); //|


void System_Decimal();
void System_D1();
void System_D2();
void System_D3();
void System_D4();
void SSD_Reset();


void Negatif_Number_Find(uint32_t);
void Number_Find(uint32_t);
void Display_Number(int);
void Display_zero();
void Floating_Display(uint16_t,uint16_t);
void Floating_Display_Negative(uint16_t,double);
void System_Decimal_Reset();
void System_Decimal_Set();
void Delay(volatile uint32_t );



#endif /* SSD_H_ */
