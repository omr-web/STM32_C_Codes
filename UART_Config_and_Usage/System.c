/*
 * System.c
 *  for this problem,Delay_ms,SysTick_Handler(),System_LED_Toggle()
 *	void System_LED_Set();
 *	void System_LED_Reset();
 *  void System_Button_Init();, functions is not necessary
int System_Button_read();
 *  Created on: 5 Ara 2020
 *      Author: ÖMER
 */

#include "stm32g0xx.h"
#include "system.h"

uint32_t counter=0;
uint8_t data_old=0;

void Delay_ms(uint32_t time){ // this function for delay time ,for example systick count from this time value to zero
	counter=time;  //
	while(counter);
}
void SysTick_Handler(){
	if(counter>0){
		counter--;// systick count from time to zero,every mili second systick come this function
	}
}


void System_Init(){
	SystemCoreClockUpdate(); // update systick
    System_LED_Init();
	System_Button_Init();
	SysTick_Config(SystemCoreClock/1000); //for 1 ms
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
void USART2_IRQHandler (){
	uint8_t data= (uint8_t)USART2->RDR;

	printchar(data);
}

void uart_tx ( uint8_t c){


	if(c!=0){
		USART2->TDR =(uint16_t)c;

		//printchar(c); // c basacak
		data_old=c;
	}





}

uint8_t uart_rx(void){
	uint8_t data= (uint8_t)USART2->RDR;


	if(data_old!=data)
		return data ;
	else
		return 0 ;




}




void UART_Init(uint32_t baud){
	/* GPIOA Set*/
	RCC->IOPENR |=(1<<0); //gpıoa clock config
	RCC->APBENR1 |= (1<<17);  //UART2 clock config

	GPIOA->MODER &= ~(3U << 2*2);  //PA2 RESET
	GPIOA->MODER |=  (2<< 2*2) ;  //PA2 SET AS alternate function

	GPIOA->MODER &= ~(3U << 2*3);  //PA3 RESET
	GPIOA->MODER |=  (2<< 2*3);   //PA3 SET AS alternate function

	GPIOA->AFR[0]  &= ~(0xFU<<4*2);  // af1... reset
	GPIOA->AFR[0]  |=  (1<<4*2);//pa2 af1

	GPIOA->AFR[0]  &= ~(0xFU<<4*3);  //af1... reset
	GPIOA->AFR[0]  |=  (1<<4*3);//pa3 af1

	USART2->CR1 =0;
	USART2->CR1 |= (1<<3); // transmitter enable
	USART2->CR1 |=(1<<2); //receiver enable
	//USART2->CR1 |=(1<<5);  //interrupt enable


	USART2->BRR = (uint16_t)(SystemCoreClock/baud);
	USART2->CR1 |=(1<<0);//USART enable

	//NVIC_SetPriority(USART2_IRQn,1);
	//NVIC_EnableIRQ(USART2_IRQn);
}

int _write(int fd,char *ptr,int len){
	(void)fd;
	for(int i=0;i<len;++i){
		printchar(ptr[i]);
	}
	return len;
}
void print(char *buf){
	int len=0;
	while(buf[len++]!= '\0'); // to find length of the buf
	_write(0,buf,len);
}
void printchar(uint8_t c){
	USART2->TDR =(uint16_t)c;
	while(!(USART2->ISR&(1<<6)));
}

int System_Button_read(){
	if((GPIOB->IDR>>7)&1){
		return 1;
	}
	else
		return 0 ;
}

