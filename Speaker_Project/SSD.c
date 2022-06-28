/*
 * SSD.c
 *
 *  Created on: 18 Ara 2020
 *      Author: ÖMER
 */
#include "stm32g0xx.h"
#include "SSD.h"
#include "Keypad.h"

void Display_zero(){// if invalid operation comprise,ssd display '----', this function print ---- for overflow and invalid operation

		Delay(500);
		System_D1();
		Display_Number(12);

		Delay(500);
		System_D2();
		Display_Number(12);

		Delay(500);
		System_D3();
		Display_Number(12);

		Delay(500);
		System_D4();
		Display_Number(12);
}
void Display_Number(int a){// a is our digit,this if-else statement ,for display digit

	if(a==0)
		System_Number0();
	else if (a==1)
		System_Number1();
	else if (a==2)
			System_Number2();
	else if (a==3)
			System_Number3();
	else if (a==4)
			System_Number4();

	else if (a==5)
			System_Number5();
	else if (a==6)
			System_Number6();
	else if (a==7)
			System_Number7();
	else if (a==8)
			System_Number8();
	else if (a==9)
				System_Number9();


}


void Number_Find(uint32_t number){// this function find the number's digit
	uint32_t binler,yuzler,onlar;
	uint32_t number_t;
	for(int j=0;j<2;j++){
		number_t=number;
		//number_t=number_t%0;
		binler=(number_t/1000);

		Delay(30);
		System_D1();

		Display_Number(binler);

		number_t=number%1000; // find hunders digits
		yuzler=(number_t /100);

		Delay(30);
		System_D2();
		Display_Number(yuzler);

		number_t=number_t%100;  // find tens digits
		onlar=number_t/10;

		Delay(30);
		System_D3();
		Display_Number(onlar);

		number_t=number_t%10;  // find ones digits

		Delay(30);
		System_D4();
		Display_Number(number_t);

	}
}
void System_Segment_Init(){
	 RCC->IOPENR |= (3U << 0); // GPIOA and GPIOB clock enable

	 GPIOA->MODER &=  ~(3U<<2*0); //pa0
	 GPIOA->MODER |=  (1U<<0);


	 GPIOA->MODER &=  ~(3U <<2*1); //pa1  as output
	 GPIOA->MODER |=  (1 << 2);

	 GPIOA->MODER &=  ~(3U <<2*4); //pa4  as output
	 GPIOA->MODER |=  (1 << 8);

	 GPIOA->MODER &=  ~(3U <<2*5); //pa5  as output
	 GPIOA->MODER |=  (1 << 10);

	 //GPIOA->MODER &=  ~(3U <<2*6); //pa6  as output
	 //GPIOA->MODER |=  (1 << 2*6);

	// GPIOA->MODER &=  ~(3U <<2*11); //pa11  as output
	// GPIOA->MODER |=  (1 << 2*11);

	 GPIOB->MODER &=  ~(3U << 0); //pB0  output
	 GPIOB->MODER |=  (1 << 0);

	 GPIOB->MODER &=  ~(3U << 2*1); //pB1  output
	 GPIOB->MODER |=  (1 << 2);

	 GPIOB->MODER &=  ~(3U << 2*2); //pB2  output
	 GPIOB->MODER |=  (1 << 4);

	 GPIOB->MODER &=  ~(3U <<2* 3); //pB3  output
	 GPIOB->MODER |=  (1 << 6);

	 GPIOB->MODER &=  ~(3U <<2* 4); //pB4  output
	 GPIOB->MODER |=  (1 << 8);

	 GPIOB->MODER &=  ~(3U <<2* 5); //pB5  output
	 GPIOB->MODER |=  (1 << 10);

	 GPIOB->MODER &=  ~(3U <<2* 6); //pB6  output
	 GPIOB->MODER |=  (1 << 12);
}


void System_Number1(){// for number 1
	GPIOB->ODR =0x79  ;
}
void System_Number2(){// for number 2

	GPIOB->ODR =0xA4  ;
}
void System_Number3(){// for number 3

	GPIOB->ODR =0xB0  ;
}
void System_Number4(){// for number 4

	GPIOB->ODR =0x99  ;
}
void System_Number5(){// for number 5

	GPIOB->ODR =0x92  ;
}
void System_Number6(){// for number 6

	GPIOB->ODR =0x2  ;
}
void System_Number7(){// for number 7

	GPIOB->ODR =0xF8  ;
}
void System_Number8(){// for number 8
	GPIOB->ODR =0  ;
}
void System_Number9(){// for number 9
	GPIOB->ODR =0x90  ;
}
void System_Number0(){// for number 0
	GPIOB->ODR =0x40  ;
}


void System_D1(){
	GPIOA->ODR |=(1<<0); //pa0 (1)
	GPIOA->ODR &= ~(1U <<1);
	GPIOA->ODR &= ~(1U <<4);
	GPIOA->ODR &= ~(1U <<5);
}
void System_D2(){
	GPIOA->ODR |=(1<<1); //PA1  (2)
	GPIOA->ODR &= ~(1U <<0);
	GPIOA->ODR &= ~(1U <<4);
	GPIOA->ODR &= ~(1U <<5);
}
void System_D3(){
	GPIOA->ODR |=(1<<4) ; //PA4   (16)
	GPIOA->ODR &= ~(1U <<1);
	GPIOA->ODR &= ~(1U <<0);
	GPIOA->ODR &= ~(1U <<5);
}
void System_D4(){
	GPIOA->ODR |=(1<<5) ; //PA5    (32)
	GPIOA->ODR &= ~(1U <<1);
	GPIOA->ODR &= ~(1U <<4);
	GPIOA->ODR &= ~(1U <<0);
}
void SSD_Reset(){
	GPIOA->ODR &= ~(1U <<0);
	GPIOA->ODR &= ~(1U <<1);
	GPIOA->ODR &= ~(1U <<4);
	GPIOA->ODR &= ~(1U <<5);
}
void System_Decimal_Set(){
	GPIOA->ODR |= (1<<11) ; // pa11 open the dat.
}
void System_Decimal_Reset(){
	GPIOA->ODR &=  ~(1<<11) ; // pa11  // close the dat .
}




