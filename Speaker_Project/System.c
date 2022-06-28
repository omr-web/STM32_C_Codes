/*
 * System.c
 *
 *  Created on: 5 Ara 2020
 *      Author: ÖMER
 */

#include "stm32g0xx.h"
#include "System.h"
#include "Keypad.h"
#include "Process.h"
#include "SSD.h"



void System_Init(){// all initialize are this function

	//SystemCoreClockUpdate(); // update
    System_Alternate_LED_Init();   // led initialize

	System_Timer_Init();  // timer3 initialize for pwm
	System_Timer2_Init(); // timer 2 initialize
}

void System_Timer_Init(){
		RCC->APBENR1 |=(1U<<1); // timer3 clock is enabled
		//RCC->APBENR2 |=(1U<<11); // timer1 clock is enabled
		TIM3->CR1=0;
		TIM3->CR1 |=(1<<7); // arpe bit set
		TIM3->CNT =0;
		TIM3->PSC=0;
		TIM3->ARR=(16000); // every 10 ms ,timer come 16000*1000
		TIM3->DIER |=(1<<0); // enable interrupts

		TIM3->CCMR1 |=(1<<3); // output compare preload enable

		TIM3->CCMR1 &= ~ (1u<<16); //0
		TIM3->CCMR1 |=(1u<<6); //1
		TIM3->CCMR1 |= (1u<<5); //1
		TIM3->CCMR1 &= ~(1u<<4);  // 0

		TIM3->CCER |=(1<<0);// (capture compare 1) enable


		TIM3->CCR1 =0x84; // old value 255

		//TIM3->AF1 |=(1<<14); //TİM3 af1 register ertsel comp1 output(?)
		TIM3->EGR |= (1<<0); // update genration
		TIM3->CR1 |= (1<<0);

		NVIC_SetPriority(TIM3_IRQn,2);
		NVIC_EnableIRQ(TIM3_IRQn);

}
void System_Timer2_Init(){
		RCC->APBENR1 |=(1U<<0); // timer2 clock is enabled
		TIM2->CR1=0;
		//TIM2->CR1 |=(1<<7); // arpe bit set
		TIM2->CNT =0;
		TIM2->PSC=0;
		TIM2->ARR=(8000); //8Hz
		TIM2->DIER |=(1<<0); // enable interrupts
		TIM2->CR1 |= (1<<0);

		NVIC_SetPriority(TIM2_IRQn,1);
		NVIC_EnableIRQ(TIM2_IRQn);

}
void TIM3_IRQHandler(){

	//TIM3->ARR =i;
	TIM3->SR &=  ~(1U<<0); // update sr registers
	//Delay(50);
	//Number_Find(i);
	//Delay(50);
}
void TIM2_IRQHandler(){
	/*
	if(i>16000)
		i=255;
	i=i+50;

	TIM3->ARR =i;
	*/

	//


	TIM3->ARR=i;
	TIM3->EGR |=(1<<0);// update generation

	TIM2->EGR |=(1<<0);
	TIM2->SR &=  ~(1U<<0); // update sr registers
	TIM2->SR &=  ~(1U<<1);
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

void Delay(volatile uint32_t s) {
    for(; s>0; s--);
}

