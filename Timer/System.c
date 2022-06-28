/*
 * System.c
 *
 *  Created on: 5 Ara 2020
 *      Author: ÖMER
 */

#include "stm32g0xx.h"
#include "system.h"

uint32_t counter=0;


void Timer_Init(){
	RCC->APBENR1 |=(1U<<0);
	TIM2->CR1=0;
	TIM2->CR1 |=(1<<7);
	TIM2->CNT =0;
	TIM2->PSC =999;
	TIM2->ARR =16000;
	TIM2->DIER |=(1<<0);
	TIM2->CR1 |=(1<<0);
	NVIC_SetPriority(TIM2_IRQn,1);
	NVIC_EnableIRQ(TIM2_IRQn);

}
/*
void TIM2_IRQHandler(){
	TIM2->SR &= ~(1U<<0);
	System_LED_Toggle();

}
*/

void System_Init(){

    System_LED_Init();
	System_Button_Init();


}

void System_LED_Init(){
	 /* Enable GPIOB and GPIOA clock */
	    RCC->IOPENR |= (3U << 0);
	 /* Setup PA0 as output */
	    GPIOA->MODER |=(1U<<0); // GPIOA_MODER first bit is equal to 1
	    GPIOA->MODER &=  ~(1U<<1);// GPIOA_MODER second bit is equal to 0

	    GPIOA->BRR |=(1<<0);
}
void System_LED_Toggle(){
	GPIOA->ODR ^=(1<<0);
}

void System_LED_Set(){
	GPIOA->ODR |=(1<<0); // GPIOA'ODR first bit is 1
}
void System_LED_Reset(){
	GPIOA->ODR &=  ~(1U<<0); // GPIOA's ODR first bit is 0
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

