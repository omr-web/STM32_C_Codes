/*
 * System.c
 *
 *  Created on: 5 Ara 2020
 *      Author: ÖMER
 */

#include "stm32g0xx.h"
#include "system.h"


uint32_t i=0 ;
uint8_t flag=0; // if flag is zero count up ,if flag is 1 count down
volatile int button =0; // button control variable
volatile int control_interrupt=0;
volatile uint32_t number=0; // our counter value.this value increse 1000 at  every seconds
							// for example if timer come to handler function five times, number should be 5000
							//after ten times our seven segment display 9999

void System_Init(){// all initialize are this function


    System_Alternate_LED_Init();   // led initialize
	System_Button_Init();  //button initialize
	System_Timer_Init();  // timer initialize
}

void System_Timer_Init(){
		RCC->APBENR1 |=(1U<<1); // timer3 clock is enabled
		TIM3->CR1=0;
		TIM3->CR1 |=(1<<7); // arpe bit set
		TIM3->CNT =0;
		TIM3->PSC=10;
		TIM3->ARR=(16000); // every 10 ms ,timer come
		TIM3->DIER |=(1<<0); // enable interrupts


		TIM3->CCMR1 |=(1<<3); // output compare preload enable

		TIM3->CCMR1 &= ~ (1u<<16); //0
		TIM3->CCMR1 |=(1u<<6); //1
		TIM3->CCMR1 |= (1u<<5); //1
		TIM3->CCMR1 &= ~(1u<<4);  // 0

		TIM3->CCER |=(1<<0);// (capture compare 1) enable


		TIM3->CCR1 =0x0;// duty cycle

		//TIM3->AF1 |=(1<<14); //TİM3 af1 register ertsel comp1 output(?)
		//TIM3->EGR |= (1<<0); // update genration
		TIM3->CR1 |= (1<<0);

		NVIC_SetPriority(TIM3_IRQn,1);
		NVIC_EnableIRQ(TIM3_IRQn);

}
void TIM3_IRQHandler(){

	if(i==16000) // if i=16000,LED brightness should decrease
		flag=1;
	else if(i==0) // if i=0,LED brightness should increase
		flag=0;

	if(flag==1)
		i=i-500;
	else if (flag==0)
		i=i+500;

	TIM3->CCR1 =i;

	TIM3->SR &=  ~(1U<<0); // update sr registers
	TIM3->SR &=  ~(1U<<1);
}



void System_Alternate_LED_Init(){
	 /* Enable GPIOB and GPIOA clock */
	    RCC->IOPENR |= (3U << 0);
	 /* Setup PA6 as alternate function */

		GPIOA->MODER &= ~(3U << 2*6);  //PA6 RESET
		GPIOA->MODER |=  (2<< 2*6) ;  //PA6 SET AS alternate function 10

		GPIOA->AFR[0]  &= ~(0xFU<<4*6);  //af1... reset
		GPIOA->AFR[0]  |=  (1<<4*6);//pa6 af1

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

