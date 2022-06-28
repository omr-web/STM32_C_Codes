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
	else if (a==11) // addition
			System_NumberA();

	else if(a==12||a==15)
			System_NumberB();
	else if(a==13)
			System_NumberC();
	else if(a==14)
			System_NumberD();


}
void Negatif_Number_Find(uint32_t number){
	uint32_t binler,yuzler,onlar;
	uint32_t number_t;
	for(int i=0;i<2;i++){
			number_t=number;
			//number_t=number_t%0;
			//binler=(number_t/1000); // we cant display -1000 we can display only -999

			Delay(50);
			System_D1();
			Display_Number(12); // for '-'

			number_t=number%1000; // find hunders digits
			yuzler=(number_t /100);

			Delay(50);
			System_D2();
			Display_Number(yuzler);

			number_t=number_t%100;  // find tens digits
			onlar=number_t/10;

			Delay(50);
			System_D3();
			Display_Number(onlar);

			number_t=number_t%10;  // find birler digits

			Delay(50);
			System_D4();
			Display_Number(number_t);
		}


}

void Number_Find(uint32_t number){// this function find the number's digit
	uint32_t binler,yuzler,onlar;
	uint32_t number_t;
	for(int i=0;i<2;i++){
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

		number_t=number_t%10;  // find birler digits

		Delay(30);
		System_D4();
		Display_Number(number_t);

	}
}
void Floating_Display_Negative(uint16_t a, double b ){ // a is number that before dat ,b is number that after dat.
	int number_t ;
		double binler,yuzler,onlar;
		if(a<10){ // number will be like that 1.002  d1's decimal will be open  -9.2 -99.2 -999.2
				//for(int i=0;i<2;i++){
					Delay(50);
					System_Decimal_Set();

					System_D1();
					Display_Number(12); // for '-'
					// add decimal..
					 // decimal is written in D1 digit
					//////////

					Delay(50);
					System_D2();
					Display_Number(a); // the number that before the dat(.)
					System_Decimal_Reset();
					number_t=b; // find hunders digits
					yuzler=(number_t /100);

					Delay(50);
					System_Decimal_Set();

					System_D3();
					Display_Number(yuzler);


					number_t=number_t%100;  // find tens digits
					onlar=number_t/10;

					Delay(50);
					System_Decimal_Set();

					System_D4(); //Note : we dont display ones digits...
					Display_Number(onlar);


			//}
		}

		else if (a<99){ // number will be like that 10.222  d2's decimal will be open
			for(int i=0;i<2;i++){
							System_Decimal_Set();
							Delay(50);
							System_D1();
							Display_Number(12); // for '-'

							// add decimal..
							// decimal is written in D1 digit

							number_t=a;
							onlar=number_t/10;

							System_Decimal_Set();
							Delay(50);
							System_D2();
							Display_Number(onlar);


							number_t=number_t%10;  // find ones digit

							Delay(50);
							System_D3();
							Display_Number(number_t);
							System_Decimal_Reset();
							// add decimal ....
							 // decimal is written in D2 digit
							////////


							number_t=b;
							binler=0,yuzler=0,onlar=0;

							yuzler=number_t/100;

							System_Decimal_Set();
							Delay(50);
							System_D4();
							Display_Number(yuzler);


					}

		}
		else if(a<999){  // number will be like that 102.222 d3's decimal will be open
			for(int i =0;i<2;i++){
				System_Decimal_Set();
				Delay(50);
				System_D1();
				Display_Number(12); // for '-'


				number_t=a;
				 // find hunders digits
				yuzler=(number_t /100);

				System_Decimal_Set();
				Delay(50);
				System_D2();
				Display_Number(yuzler);
				number_t=number_t%100;
				onlar=number_t/10; // find tens digit

				System_Decimal_Set();
				Delay(50);
				System_D3();
				Display_Number(onlar);
				number_t=number_t%10;  // find ones  digit

				Delay(50);
				System_D4();
				Display_Number(number_t);
				System_Decimal_Reset();
				// there is no place for b(after dot)
			}

		}
		else{
				Number_Find(a);// if b is bigger than 999,ssd'S four digits display for b's digits
			}
	binler=0,yuzler=0,onlar=0,number_t=0;
	}

void Floating_Display(uint16_t a, uint16_t b){// first argument is before dat,second argument is after dat.
	int number_t ;
	double binler,yuzler,onlar;
	if(a<10){ // number will be like that 1.002  d1's decimal will be open  2.111   22.22  223.
			for(int i=0;i<1;i++){

				Delay(100);
				System_D1();
				Display_Number(a);
				System_Decimal_Reset();
				// add function for decimal..
				 // decimal is written in D1 digit
				//////////

				number_t=b; // find hunders digits
				yuzler=(number_t /100);

				System_Decimal_Set();
				Delay(100);
				System_D2();
				Display_Number(yuzler);



				number_t=number_t%100;  // find tens digits
				onlar=number_t/10;

				System_Decimal_Set();
				Delay(100);
				System_D3();
				Display_Number(onlar);
				// add function for decimal..


				number_t=number_t%10;  // find birler digits

				System_Decimal_Set();
				Delay(100);
				System_D4();
				Display_Number(number_t);
				// add function for decimal..
				//Delay(100);
		}
	}

	else if (a<99){ // number will be like that 10.222  d2's decimal will be open
		for(int i=0;i<2;i++){
						number_t=a;
						onlar=number_t/10;

						System_Decimal_Set();
						Delay(50);
						System_D1();
						Display_Number(onlar);

						number_t=number_t%10;  // find birler digits


						Delay(50);
						System_D2();
						Display_Number(number_t);
						System_Decimal_Reset();
						// add decimal ....
						 // decimal is written in D2 digit
						////////

						number_t=b;
						binler=0,yuzler=0,onlar=0;
						/*
						//number_t=b%1000; // find hunders digits
						yuzler=(number_t /100);

						Delay(50);
						System_D3();
						Display_Number(yuzler);
						*/

						  // find hundreds digits
						yuzler=number_t/100;
						System_Decimal_Set();
						Delay(50);
						System_D3();
						Display_Number(yuzler);

						number_t=number_t%100;  // find tens digits
						onlar=number_t/10;

						System_Decimal_Set();
						Delay(50);
						System_D4();
						Display_Number(onlar);

				}

	}
	else if(a<999){  // number will be like that 102.222 d3's decimal will be open
		for(int i =0;i<2;i++){
			number_t=a;
			 // find hunders digits
			yuzler=(number_t /100);

			System_Decimal_Set();
			Delay(50);
			System_D1();
			Display_Number(yuzler);

			number_t=number_t%100;
			onlar=number_t/10; // find tens digit

			System_Decimal_Set();
			Delay(50);
			System_D2();
			Display_Number(onlar);

			number_t=number_t%10;  // find ones  digit

			Delay(50);

			System_D3();
			Display_Number(number_t);
			System_Decimal_Reset();
			// add decimal ...
			 // decimal is written in D3 digit

			number_t=b/100;
			System_Decimal_Set();
			Delay(50);
			System_D4();
			Display_Number(number_t);

		}

	}
	else{
		Number_Find(a);// if b is bigger than 999,ssd'S four digits display for b's digits
	}
binler=0,yuzler=0,onlar=0,number_t=0;
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

	 GPIOA->MODER &=  ~(3U <<2*6); //pa6  as output
	 GPIOA->MODER |=  (1 << 2*6);

	 GPIOA->MODER &=  ~(3U <<2*11); //pa11  as output
	 GPIOA->MODER |=  (1 << 2*11);

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


void System_Number1(){
	GPIOB->ODR =0x79  ;
}
void System_Number2(){

	GPIOB->ODR =0xA4  ;
}
void System_Number3(){

	GPIOB->ODR =0xB0  ;
}
void System_Number4(){

	GPIOB->ODR =0x99  ;
}
void System_Number5(){

	GPIOB->ODR =0x92  ;
}
void System_Number6(){

	GPIOB->ODR =0x2  ;
}
void System_Number7(){

	GPIOB->ODR =0xF8  ;
}
void System_Number8(){
	GPIOB->ODR =0  ;
}
void System_Number9(){
	GPIOB->ODR =0x90  ;
}
void System_Number0(){
	GPIOB->ODR =0x40  ;
}
void System_NumberA(){ // for addition
	GPIOB->ODR =0x8  ;
}
void System_NumberB(){ // For substraction
	GPIOB->ODR =0x3F  ;
}
void System_NumberC(){ // For substraction
	GPIOB->ODR =0x4E  ;
}
void System_NumberD(){ // For Division
	GPIOB->ODR =0x4F  ;
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


void Delay(volatile uint32_t s) {
    for(; s>0; s--);
}

