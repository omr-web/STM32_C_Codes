/*
 * System.c
 *
 *  Created on: 5 Ara 2020
 *      Author: ÖMER
 */

#include "stm32g0xx.h"
#include "system.h"



volatile int button =0; // button control variable
volatile int control_interrupt=0;
volatile uint32_t number=0; // our counter value.this value increse 1000 at  every seconds
							// for example if timer come to handler function five times, number should be 5000
							//after ten times our seven segment display 9999
void Update_WatchDog(){
	IWDG->SR=0x7;
}
void System_Init(){// all initialize are this function
	IWDG->KR=0x5555;
	IWDG->PR=0x7;
	IWDG->RLR=0xFFF;
	IWDG->WINR=0xFFF;
	IWDG->KR=0xCCCC;
	System_Segment_Init(); // SSD initialize
    System_LED_Init();   // led initialize
	System_Button_Init();  //button initialize
	System_Timer_Init();  // timer initialize
}
void Display_zero(){ // if count process finish or user don't push button any time ,ssd display four digit zero
		Delay(500);
		System_D1();
		Display_Number(0);

		Delay(500);
		System_D2();
		Display_Number(0);

		Delay(500);
		System_D3();
		Display_Number(0);

		Delay(500);
		System_D4();
		Display_Number(0);
}
void Normal_Mode(){

	while(1){
		int b =System_Button_read();
		if (b==1)
			System_Timer_Init();
		else{
			for(int i=0;i<100;i++){
				Delay(500);
				System_D1();
				Display_Number(0);

				Delay(500);
				System_D2();
				Display_Number(0);

				Delay(500);
				System_D3();
				Display_Number(0);

				Delay(500);
				System_D4();
				Display_Number(0);
			}
		}

	}
}

void System_Timer_Init(){
		RCC->APBENR1 |=(1U<<1);
		TIM3->CR1=0;
		TIM3->CR1 |=(1<<7);
		TIM3->CNT =0;
		TIM3->PSC=999;
		TIM3->ARR=(16000); // 1 sn
		TIM3->DIER |=(1<<0);
		TIM3->CR1 |= (1<<0);
		NVIC_SetPriority(TIM3_IRQn,1);
		NVIC_EnableIRQ(TIM3_IRQn);

}
void TIM3_IRQHandler(){
		for(int j=0;j<100;j++){
			number=number+1; // every second,number increase 1000 times and we can see display
			if(number==9999){ // if number is 9999 ,counter process should finish
				number=0;

			}
			Number_Find(number);
		}



	TIM3->SR &=  ~(1U<<0);
	Update_WatchDog();
}


void Display_Number(int a){
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
	else
		System_Number9();

}
void Number_Find(uint32_t number){
	uint32_t binler,yuzler,onlar;
	uint32_t number_t;
	for(int i=0;i<2;i++){
		number_t=number;
		//number_t=number_t%0;
		binler=(number_t/1000);

		Delay(60);
		System_D1();
		Display_Number(binler);

		number_t=number%1000; // find hunders digits
		yuzler=(number_t /100);

		Delay(60);
		System_D2();
		Display_Number(yuzler);

		number_t=number_t%100;  // find tens digits
		onlar=number_t/10;

		Delay(60);
		System_D3();
		Display_Number(onlar);

		number_t=number_t%10;  // find birler digits

		Delay(60);
		System_D4();
		Display_Number(number_t);
	}
}

void System_Segment_Init(){
	 RCC->IOPENR |= (3U << 0);

	 GPIOA->MODER &=  ~(3U<<2*0); //pa0
	 GPIOA->MODER |=  (1U<<0);


	 GPIOA->MODER &=  ~(3U <<2*1); //pa1  as output
	 GPIOA->MODER |=  (1 << 2);

	 GPIOA->MODER &=  ~(3U <<2*4); //pa4  as output
	 GPIOA->MODER |=  (1 << 8);

	 GPIOA->MODER &=  ~(3U <<2*5); //pa5  as output
	 GPIOA->MODER |=  (1 << 10);

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
void System_D_Reset(){
	GPIOA->ODR =0;
}


void System_D1(){
	GPIOA->ODR =1; //pa0
}
void System_D2(){
	GPIOA->ODR =2; //PA1
}
void System_D3(){
	GPIOA->ODR =16 ; //PA4
}
void System_D4(){
	GPIOA->ODR=32; //PA5
}
void System_LED_Init(){
	 /* Enable GPIOB and GPIOA clock */
	    RCC->IOPENR |= (3U << 0);
	 /* Setup PA6 as output */
	    GPIOA->MODER &=  ~(3U <<2* 6); //pA6  output
	    GPIOA->MODER |=  (1 << 12);

	    GPIOA->BRR |=(1<<0);
}
void System_LED_Toggle(){
	GPIOA->ODR ^=(1<<6);
}

void System_LED_Set(){
	GPIOA->ODR |=(1<<6); // GPIOA'ODR first bit is 1
}
void System_LED_Reset(){
	GPIOA->ODR &=  ~(1U<<6); // GPIOA's ODR first bit is 0
}



void System_Button_Init(){
	/* Enable GPIOB and GPIOA clock */
	    RCC->IOPENR |= (3U << 0);
    /*set pb7 as input */
	    GPIOB->MODER &= ~(3U << 2*7);
}


int System_Button_read(){
	if((GPIOB->IDR>>7)&1){
		return 1;
	}
	else
		return 0 ;
}
void Delay(volatile uint32_t s) {
    for(; s>0; s--);
}

