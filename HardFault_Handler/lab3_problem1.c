/*
 * main.c
 *
 * author: Omer Cebeci 171024007
 */

#include "stm32g0xx.h"
#include <stdio.h>
#include<stdlib.h>
#define LEDDELAY    5000
#define LEDDELAY2    500000
void delay(volatile uint32_t);

void HardFault_Handler(){
	GPIOA->ODR  |= (1<<4);
	delay(LEDDELAY2);
	SCB->AIRCR=0x5FA8004;//reset the software
	Reset_Handler();

}
int main(void) {
    /* Enable GPIOB and GPIOA clock */
    RCC->IOPENR |= (3U << 0);
    /* Setup PB3 as input */
    GPIOB->MODER &= ~(3U << 2*3);

    /* Setup PA4 as output */
    GPIOA->MODER &= ~(3U << 2*4);
    GPIOA->MODER |= (1U << 2*4);


    /* Setup PB3 as input */
       GPIOB->MODER &= ~(3U << 2*3);
       int a =rand() %2;

    while(1) {
    	//GPIOB->ODR &=  ~(1<<3);
    	//delay(LEDDELAY);
    	if((GPIOB->IDR>>3)&1){
    		__asm("ldr r1,=#0x20000001");
    		//__asm("ldr r1,=#0x8100000");
    		__asm("ldr r5 ,[r1]");
    	}

    }

    return 0;
}
void delay(volatile uint32_t s) {
    for(; s>0; s--);
}


