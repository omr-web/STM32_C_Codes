/*
 * main.c
 *
 * author: Omer Cebeci 171024007
 */

#include "stm32g0xx.h"

#define LEDDELAY    11949990

void delay(volatile uint32_t);


void EXTI2_3_IRQHandler (){  // FOR  PA0 LED

	GPIOA->ODR |=(1U<<0);
	delay(LEDDELAY);
	GPIOA->ODR &= ~(1U<<0);

	EXTI->RPR1 |=(1<<3);
}
void EXTI4_15_IRQHandler(){  // FOR PA1 LED


	GPIOA->ODR |=(1<<1);
	delay(LEDDELAY);
	GPIOA->ODR &= ~(1U<<1);
	delay(LEDDELAY);
	EXTI->RPR1 |=(1<<7);

}
int main(void) {

    /* Enable GPIOB and GPIOA clock */
    RCC->IOPENR |= (3U << 0);

    /* Setup PB3 as input */
    GPIOB->MODER &= ~(3U << 2*3);

    /* Setup PA0 as output */
    GPIOA->MODER |=(1U<<0); // GPIOA_MODER first bit is equal to 1
    GPIOA->MODER &=  ~(1U<<1);// GPIOA_MODER second bit is equal to 0

    /* Setup PA1 as output */
    GPIOA->MODER |=(1U<<2*1); // GPIOA_MODER third bit is equal to 1
    GPIOA->MODER &=  ~(1U<<3);// GPIOA_MODER fourth bit is equal to 0


    /* Setup PB7 as input */
    GPIOB->MODER &= ~(3U << 2*7);
    /* first interrupt is at pb3 second interrupt is at pB7*/

    /* arrangement pb3 as interrupt*/
    EXTI->RTSR1 |=(1U<<3);
    EXTI->EXTICR[0] |= (1U<<8*3);
    EXTI->IMR1 |=(1<<3);
    NVIC_SetPriority(EXTI2_3_IRQn,1);
    NVIC_EnableIRQ(EXTI2_3_IRQn);


    /* arrangement pB7 as interrupt*/
    EXTI->RTSR1 |=(1U<<7);
    EXTI->EXTICR[1] |=  (1u<<8*3);
    EXTI->IMR1 |=(1<<7);
    NVIC_SetPriority(EXTI4_15_IRQn,0);  // pB7
    NVIC_EnableIRQ(EXTI4_15_IRQn);

    while(1) {

    }

    return 0;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
