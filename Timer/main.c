/*
 * main.c
 *
 * author: Omer Cebeci 171024007
 */

#include "stm32g0xx.h"
#define LEDDELAY    1600000

void delay(volatile uint32_t);

void TIM3_IRQHandler(){
	GPIOA->ODR ^= (1<<0);
	TIM3->SR &=  ~(1U<<0);
}

void timer_config(uint32_t a){
	RCC->APBENR1 |=(1U<<1);
	TIM3->CR1=0;
	TIM3->CR1 |=(1<<7); // we set buffer
	TIM3->CNT =0;
	TIM3->PSC=(10*a); // this two instructions arrange one delay time,f.ex if a=1000 one toggle lead tens seconds ,
	TIM3->ARR=(16000);// this timer's clock 16MHz
	TIM3->DIER |=(1<<0); // enable interrupt
	TIM3->CR1 |= (1<<0);// enable control register
	NVIC_SetPriority(TIM3_IRQn,0);// set timer'S priority
	NVIC_EnableIRQ(TIM3_IRQn); // enable NVIC interrupt

}

uint32_t b =1000;
int main(void) {
	/* Enable GPIOB and GPIOA clock */
		    RCC->IOPENR |= (3U << 0);
	/* Setup PA0 as output */
		    GPIOA->MODER |=(1U<<0); // GPIOA_MODER first bit is equal to 1
		    GPIOA->MODER &=  ~(1U<<1);// GPIOA_MODER second bit is equal to 0

		    GPIOA->BRR |=(1<<0);

  /*set pb7 as input */
		 GPIOB->MODER &= ~(3U << 2*7);

		 timer_config(b);
	while(1) {
			if((GPIOB->IDR>>7)&1){
					delay(3149888);//delay for noise // sometimes if I push one time ,change of b is not 100 for example 500.I use delay to  prevent

					if(b==0){
						b=1000;
					}
					b=b-100; // I reduce the toggle seconds
					timer_config(b);// I initiliaze timer again ( for new toggle time)
				}

			}
	return 0;

    }


void delay(volatile uint32_t s) {
    for(; s>0; s--);
}

