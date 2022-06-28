/*
 * System.c
 *
 *  Created on: 6 Ocak 2021
 *      Author: ÖMER
 */

#include "stm32g0xx.h"
#include "system.h"


uint16_t pot_value;
float led1_value ;
float led2_value;

int ratio=1 ;
int b ;
uint32_t c=0 ;
void System_Init(){// all initialize are this function

	//UART_Init(9600);
   // System_Analog_LED_Init();   // pot initialize

    LED_Init();  // led initialize
    ADC_Init();  // adc initialize
    //Timer Initializes
    System_Timer14_Init();
    System_Timer3_Init();
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

			//ADC1->ISR &= ~(1 << 0);

			ADC1->CR |= (1U << 0);				/* ENABLE ADC */
			while (ADC1->ISR & (1 << 0));		/* WILL NOT COME OUT UNTIL ADC READY */


			ADC1->CR |= (1U << 2);  //start conversion

}

void System_Timer3_Init(){  // timer3 was setted as pwm for led1
		RCC->APBENR1 |=(1U<<1); // timer3 clock is enabled
		TIM3->CR1=0;
		TIM3->CR1 |=(1<<7); // arpe bit set
		TIM3->CNT =0;
		TIM3->PSC=0;
		TIM3->ARR=(16000); // every 10 ms ,timer come
		TIM3->DIER |=(1<<0); // enable interrupts


		TIM3->CCMR1 |=(1<<3); // output1 compare preload enable

		TIM3->CCMR1 &= ~ (1u<<16); //0
		TIM3->CCMR1 |=(1u<<6); //1
		TIM3->CCMR1 |= (1u<<5); //1
		TIM3->CCMR1 &= ~(1u<<4);  // 0
		TIM3->CCER |=(1<<0);// (capture compare 1) enable
		TIM3->CCR1 =1600;// duty cycle

#if(0)
		// CH2 SETTING FOR PWM
			TIM3->CCMR1 &= ~(0X7U << 12);
			TIM3->CCMR1 &= ~(0X1U << 24);
			TIM3->CCMR1 |= (0X6U << 12);
			TIM3->CCMR1 |= (1U << 11);

#endif

			TIM3->CCMR1 &= ~ (1u<<24); //0
			TIM3->CCMR1 |=(1u<<14); //1
			TIM3->CCMR1 |= (1u<<13); //1
			TIM3->CCMR1 &= ~(1u<<12);  // 0





			TIM3->CCER |= (1U << 4);		/* ENABLE CAPTURE/COMPARE 2 OUTPUT */
			TIM3->CCR2 = 1600;		/* CHANNEL 2 duty cycle */


		TIM3->EGR |= (1<<0); // update generation
		TIM3->CR1 |= (1<<0);

		NVIC_SetPriority(TIM3_IRQn,0);
		NVIC_EnableIRQ(TIM3_IRQn);

}


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
	pot_value = ADC_Data(); // receive data from adc
	/* this value should between 0-4095 because, adc's setted type, and also led1_value+led2_value should be 4095*/
	/*and ratio between led1_value and led2_value, determine the brightness of leds*/
	led1_value =pot_value;
	led2_value=255-led1_value;

	if(led1_value>led2_value){
		if(led1_value==255){  // this "if" for led1 %100, led2 %0
			TIM3->CCR1 =7200;
			TIM3->CCR2 =0;
		}
		else{
			ratio=led1_value/led2_value;// find ratio
			/*determine the brightness of led  */
			TIM3->CCR1 =1600*ratio;
			TIM3->CCR2 =1600;
			TIM3->EGR |= (1<<0); // update generation
		}
	}
	else{
		if(led2_value==255){// this "if" for led2 %100, led1 %0
					TIM3->CCR1 =0;
					TIM3->CCR2 =7200;
				}
				else{
					ratio=led2_value/led1_value; // find ratio
					/*determine the brightness of led  */
					TIM3->CCR1 =1600;
					TIM3->CCR2 =1600*ratio;
					TIM3->EGR |= (1<<0); // update generation
				}
	}



	TIM14->SR &=  ~(1U<<0); // update sr registers
	TIM14->SR &=  ~(1U<<1);
}

void TIM3_IRQHandler(){ // this handler do nothing,this timer produce only PWM signal
	TIM3->SR &=  ~(1U<<1);
	TIM3->SR &= ~(1U << 0);
}


void System_Analog_LED_Init(){
	 /* Enable GPIOB and GPIOA clock */
	    RCC->IOPENR |= (3U << 0);
	 /* Setup PA6 as alternate function */

		GPIOB->MODER &= ~(3U << 2*2);  //Pb2 RESET
		GPIOB->MODER |=  (3<< 2*2) ;  //PB2 SET AS analog input  11
}

void LED_Init(){
	 /* Enable GPIOB and GPIOA clock */
		RCC->IOPENR |= (3U << 0);
	  /* Setup PA6 as alternate function */

	GPIOB->MODER &= ~(3U << 2*4);  //Pb4 RESET
    GPIOB->MODER |=  (2<< 2*4) ;  //Pb4 SET AS alternate function 10


	GPIOB->AFR[0]  &= ~(0xFU<<4*4);  //af0... reset
	GPIOB->AFR[0]  |=  (1<<4*4);//pb4 af0

	 ///////////*  Pb5 set as alternate function */
	GPIOB->MODER &= ~(3U << 2*5);  //Pb5 RESET
	GPIOB->MODER |=  (2<< 2*5) ;  //Pb5 SET AS alternate function 10


	GPIOB->AFR[0]  &= ~(0xFU<<4*5);  //af0... reset
	GPIOB->AFR[0]  |=  (1<<4*5);//pa4 af0
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

void Delay(volatile uint32_t s) {
    for(; s>0; s--);
}

uint16_t ADC_Data(){ // this function for receive the data from ADC...
	ADC1->CR |=(1<<2);
	b=ADC1->ISR;
	    	b=(b>>2)&1;
	    	if((b)==1){
	    			return ADC1->DR;
	    	}
}
