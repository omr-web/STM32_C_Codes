/*
 * main.c
 *
 * author: Omer Cebeci 171024007
 *
 *
 */

#include "stm32g0xx.h"

#define LEDDELAY    1600000

void delay(volatile uint32_t);


void EXTI2_3_IRQHandler (){

	GPIOA->ODR |=(1<<1);
	EXTI->RPR1 |=(1<<3);
}
int main(void) {

    /* Enable GPIOB and GPIOA clock */
    RCC->IOPENR |= (3U << 0);

    /* Setup PB3 as input */
    GPIOB->MODER &= ~(3U << 2*3);

    /* Setup PA0 as output */
    GPIOA->MODER |=(1U<<2); // GPIOA_MODER third bit is equal to 1
    GPIOA->MODER &=  ~(1U<<3);// GPIOA_MODER fourth bit is equal to 0

    EXTI->RTSR1 |=(1U<<3);
    EXTI->EXTICR[0] |= (1U<<8*3);
    EXTI->IMR1 |=(1<<3);
    NVIC_SetPriority(EXTI2_3_IRQn,0);
    NVIC_EnableIRQ(EXTI2_3_IRQn);


    while(1) {
    	GPIOA->ODR &=  ~(1U<<1);
    }

    return 0;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
