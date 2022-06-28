/*
 * System.c
 *
 *  Created on: 6 Ocak 2021
 *      Author: ÖMER
 */

#include "stm32g0xx.h"
#include "system.h"



int ratio=1 ;
int b ;
uint32_t c=0 ;


void System_Init(){// all initialize are this function

	UART_Init(9600);
	System_Segment_Init();
	System_Button_Init();

    ADC_Init();
   // System_Timer14_Init();

}
void ADC_Init(){

		RCC->IOPENR |= (1U << 0);			/* A BLOCK RCC OPEN */
		GPIOA->MODER &= ~(3U << 2 * 7);		/* PA7 ANALOG MODE CLEAR */
		GPIOA->MODER |= (3U << 2 * 7);		/* PA7 ANALOG MODE */

		RCC->APBENR2 |= (1U << 20);			/* ENABLE ADC CLOCK */
		ADC1->CR |= (1U << 28);	 			/* ENABLE ADC VOLTAGE REGULATOR */
		Delay(100);						/* WAIT FOR ADC ENABLE  */

		ADC1->CR |= (1U << 31);				/* ENABLE ADC CALIBRATION  */
		while (ADC1->CR & (1 << 31));		/* WILL NOT COME OUT WITHOUT ADC CALIBRATION */

		ADC1->CFGR1 |=(1<<4);  // 8 bits resolution

		ADC1->CHSELR |= (1U << 7);			/* ADC CHANNEL SELECTION REGISTER (PA7) */
		ADC1->CFGR1 |= (1U << 13);

		ADC1->ISR &= ~(1 << 0);

		ADC1->CR |= (1U << 0);				/* ENABLE ADC */
		while (ADC1->ISR & (1 << 0));		/* WILL NOT COME OUT UNTIL ADC READY */


		ADC1->CR |= (1U << 2);  //start conversion
}



/////////////////////////Timer functions
void System_Timer14_Init(){
			RCC->APBENR2 |=(1U<<15); // timer14 clock is enabled
			TIM14->CR1=0;
			TIM14->CR1 |=(1<<7); // arpe bit set
			TIM14->CNT =0;
			TIM14->PSC=0;
			TIM14->ARR=(16000); // every 10 ms ,timer come
			TIM14->DIER |=(1<<0); // enable interrupts

			TIM14->CR1 |= (1<<0);
			NVIC_SetPriority(TIM14_IRQn ,1);
			NVIC_EnableIRQ(TIM14_IRQn);
}

void TIM14_IRQHandler   (){


	TIM14->SR &=  ~(1U<<0); // update sr registers
	TIM14->SR &=  ~(1U<<1);
}
//////////////////////////////////////////////////////////
void LED_Init(){ // not using this function...
	 /* Enable GPIOB and GPIOA clock */
		RCC->IOPENR |= (3U << 0);
	  /* Setup PA6 as alternate function */

	GPIOB->MODER &= ~(3U << 2*4);  //Pb4 RESET
    GPIOB->MODER |=  (2<< 2*4) ;  //PA4 SET AS alternate function 10

}


////////////////uart and printf functions
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
///////////////////////////////////
void Delay(volatile uint32_t s) {
    for(; s>0; s--);
}

////////////////////////////BUTTONS FUNCTIONS
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
//////////////////////// SSD functions
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


/////////////////////////////////////
uint16_t ADC_Data(){
	ADC1->CR |=(1<<2);
	b=ADC1->ISR;
	    	b=(b>>2)&1;
	    	if((b)==1){
	    			return ADC1->DR;
	    	}
}
