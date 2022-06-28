/*
 * System.c
 *
 *  Created on: 5 Ara 2020
 *      Author: ÖMER
 */

#include "stm32g0xx.h"
#include "system.h"

uint32_t binler,yuzler,onlar;
uint32_t number_t,number;
uint32_t c=0 ;
uint32_t flag=1; // if flag is zero,we write ones digits, else we write tens digits
uint32_t j=1000;
uint32_t uart_flag=0;
uint32_t duty_data =0; //onlar_bas*10+ones
uint8_t birler_bas =0; // birler_bas
uint8_t onlar_bas =0;

volatile int button =0; // button control variable
volatile int control_interrupt=0;


void System_Init(){// all initialize are this function


    System_Alternate_LED_Init();   // led initialize
    System_Keypad_Output_Init();
    System_Keypad_Set();
    System_Keypad_Reset();
    System_Keypad_Button_Init();
	System_Timer_Init();  // timer initialize
	UART_Init(9600);
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


		TIM3->CCR1 =0x0;

		//TIM3->AF1 |=(1<<14); //TİM3 af1 register ertsel comp1 output(?)
		TIM3->EGR |= (1<<0); // update genration
		TIM3->CR1 |= (1<<0);

		NVIC_SetPriority(TIM3_IRQn,3);
		NVIC_EnableIRQ(TIM3_IRQn);

}
uint8_t Display_Number(uint8_t a){
	if(a==0)  // these return valus are ASCII values for example if number is 0 , we have to send UART 48 for displaying 0.
		return 48 ;
	else if(a==1)
		return 49;
	else if(a==2)
		return 50;
	else if(a==3)
		return 51;
	else if (a==4)
		return 52;
	else if(a==5)
		return 53;
	else if (a==6)
		return 54;
	else if(a==7)
		return 55;
	else if(a==8)
		return 56;
	else
		return 57;
}
void TIM3_IRQHandler(){
	uart_flag=uart_flag+10;
	if(uart_flag==2000){
				number=TIM3->CCR1;
				number_t=number;
				number_t=(number_t)/10000; // tens of thousand digit
				printNumber(Display_Number(number_t));

				number_t=(number%10000);
				binler=number_t/1000; // thousands digit
				printNumber(Display_Number(binler));



				number_t=(number)%1000; // find hunderds digit
				yuzler=(number_t /100);
				printNumber(Display_Number(yuzler));


				number_t=number_t%100;  // find tens digit
				onlar=number_t/10;
				printNumber(Display_Number(onlar));

				number_t=number_t%10; // find ones digit
				printNumber(Display_Number(number_t));
				uart_flag=0;
	}



	TIM3->SR &=  ~(1U<<0);
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
void EXTI0_1_IRQHandler (){ //c1
	System_Keypad_Reset();// all output reset AS 0V

	GPIOA->ODR |=(1<<0);  //R1 Check
	if((GPIOB->IDR>>1)&1){ // if it is true ,user push the one;
		if(flag==1){ // in this if statement ,we find incoming number'S digit ones or tens
			onlar_bas=1;
			flag=0;
		}
		else{
			birler_bas=1;
			flag=1;
		}

	}
	else{
		GPIOA->ODR &=  ~(1U <<0);// user dont push '1' (R1)
		GPIOA->ODR |=(1<<1);  //R2 Check
		if((GPIOB->IDR>>1)&1){ // if it is true ,user push the '4';
			         //TIM3->CCR1 =7111; //400
			if(flag==1){
						onlar_bas=4;
						flag=0;
					}
					else{
						birler_bas=4;
						flag=1;
					}

				}

		else {
			GPIOA->ODR &=  ~(1U <<1);// user dont push '4'	(R2)
			GPIOA->ODR |=(1<<4);  //R3 Check  PA4
			if((GPIOB->IDR>>1)&1){ // if it is true ,user push the '7';
				if(flag==1){
										onlar_bas=7;
										flag=0;
									}
									else{
										birler_bas=7;
										flag=1;
									}


			}
			else{
				GPIOA->ODR &=  ~(1U <<4);// user dont push '7'	(PA4)
				GPIOA->ODR |=(1<<5);  //R4 Check
				if((GPIOB->IDR>>1)&1){ // if it is true ,user push the '*';

				}

			}

		}

	}
	System_Keypad_Set();// all output set AS  5V
	EXTI->RPR1 |=(1<<1);
}
void EXTI4_15_IRQHandler (){ // c4
	System_Keypad_Reset();// all output set to zero 0V

	GPIOA->ODR |=(1<<0);  //R1 Check
	if((GPIOB->IDR>>4)&1){ // if it is true ,user push the 'A';
		TIM3->CCR1 =100;
	}
	else{
		GPIOA->ODR &=  ~(1U <<0);// user dont push 'A' (R1)
		GPIOA->ODR |=(1<<1);  //R2 Check
		if((GPIOB->IDR>>4)&1){ // if it is true ,user push the 'B';
			TIM3->CCR1 =100;
		}
		else {
			GPIOA->ODR &=  ~(1U <<1);// user dont push 'B'	(R2)
			GPIOA->ODR |=(1<<4);  //R3 Check  PA4
			if((GPIOB->IDR>>4)&1){ // if it is true ,user push the 'C';
				TIM3->CCR1 =100;
			}
			else{
				GPIOA->ODR &=  ~(1U <<4);// user dont push 'C'	(PA4)
				GPIOA->ODR |=(1<<5);  //R4 Check
				if((GPIOB->IDR>>4)&1){ // if it is true ,user push the 'D';
					TIM3->CCR1 =100;
				}

			}

		}

	}

	System_Keypad_Set();// all output set AS  5V
	EXTI->RPR1 |=(1<<4);
}
void EXTI2_3_IRQHandler (){ // c2 and c3
	System_Keypad_Reset();// all output set to zero 0V
	if((EXTI->RPR1>>2)&1){  /// ???????????????????????????????
		GPIOA->ODR |=(1<<0);  //R1 Check
		if((GPIOB->IDR>>2)&1){ // if it is true ,user push the '2';
			if(flag==1){
						onlar_bas=2;
						flag=0;
					}
					else{
						birler_bas=2;
						flag=1;
					}

				}

		else{
			GPIOA->ODR &=  ~(1U <<0);// user dont push '2' (R1)
			GPIOA->ODR |=(1<<1);  //R2 Check
			if((GPIOB->IDR>>2)&1){ // if it is true ,user push the '5';
				if(flag==1){
							onlar_bas=5;
							flag=0;
						}
						else{
							birler_bas=5;
							flag=1;
						}

					}

			else {
				GPIOA->ODR &=  ~(1U <<1);// user dont push '5'	(R2)
				GPIOA->ODR |=(1<<4);  //R3 Check  PA4
				if((GPIOB->IDR>>2)&1){ // if it is true ,user push the '8';
					if(flag==1){
								onlar_bas=8;
								flag=0;
							}
							else{
								birler_bas=8;
								flag=1;
							}

						}

				else{
					GPIOA->ODR &=  ~(1U <<4);// user dont push '8'	(PA4)
					GPIOA->ODR |=(1<<5);  //R4 Check
					if((GPIOB->IDR>>2)&1){ // if it is true ,user push the '0';
						if(flag==1){
									onlar_bas=0;
									flag=0;
								}
								else{
									birler_bas=0;
									flag=1;
								}


					}

				}

			}

		}
		EXTI->RPR1 |=(1<<2);
	}
	else{
		GPIOA->ODR |=(1<<0);  //R1 Check
		if((GPIOB->IDR>>3)&1){ // if it is true ,user push the '3';
			if(flag==1){
						onlar_bas=3;
						flag=0;
					}
					else{
						birler_bas=3;
						flag=1;
					}


		}
		else{
				GPIOA->ODR &=  ~(1U <<0);// user dont push '3' (R1)
				GPIOA->ODR |=(1<<1);  //R2 Check
				if((GPIOB->IDR>>3)&1){ // if it is true ,user push the '6';
					if(flag==1){
								onlar_bas=6;
								flag=0;
							}
							else{
								birler_bas=6;
								flag=1;
							}

						}

				else {
						GPIOA->ODR &=  ~(1U <<1);// user dont push '6'	(R2)
						GPIOA->ODR |=(1<<4);  //R3 Check  PA4
						if((GPIOB->IDR>>3)&1){ // if it is true ,user push the '9';
							if(flag==1){
										onlar_bas=9;
										flag=0;
									}
									else{
										birler_bas=9;
										flag=1;
									}


						}
						else{
								GPIOA->ODR &=  ~(1U <<4);// user dont push '9'	(PA4)
								GPIOA->ODR |=(1<<5);  //R4 Check
						if((GPIOB->IDR>>3)&1){ // if it is true ,user push the '#';
							duty_data=(16000*((onlar_bas*10)+birler_bas))/100;
							TIM3->CCR1=duty_data;
							}

						}

					}

		}

		EXTI->RPR1 |=(1<<3);
	}
	System_Keypad_Set();// all output set AS  5V
}
void System_Keypad_Output_Init(){

	 GPIOA->MODER &=  ~(3U<<2*0); //pa0 as output ,in the keypad R1
	 GPIOA->MODER |=  (1U<<0);


	 GPIOA->MODER &=  ~(3U <<2*1); //pa1  as output ,in the keypad R2
	 GPIOA->MODER |=  (1 << 2);

	 GPIOA->MODER &=  ~(3U <<2*4); //pa4  as output ,in the keypad R3
	 GPIOA->MODER |=  (1 << 8);

	 GPIOA->MODER &=  ~(3U <<2*5); //pa5  as output ,in the keypad R4
	 GPIOA->MODER |=  (1 << 10);
}
void System_Keypad_Set(){
	GPIOA->ODR |= (1<<0);  //pa0 set,R1 set
	GPIOA->ODR |= (1<<1);  //pa1 set,R2 set
	GPIOA->ODR |= (1<<4);  //pa4 set,R3 set
	GPIOA->ODR |= (1<<5);  //pa5 set,R4 set

}
void System_Keypad_Reset(){
	GPIOA->ODR &=  ~(1U <<0); //pa0 reset,R1 reset
	GPIOA->ODR &=  ~(1U <<1); //pa1 reset,R2 reset
	GPIOA->ODR &=  ~(1U <<4); //pa4 reset,R3 reset
	GPIOA->ODR &=  ~(1U <<5);  //pa5 reset,R4 reset
}

void System_Keypad_Button_Init(){
	/*set pb1 as input */ // in keypad C1
		GPIOB->MODER &= ~(3U << 2*1);
		GPIOB->PUPDR |= (2U << 2*1);
	/*set pb2 as input */ // in keypad C2
		GPIOB->MODER &= ~(3U << 2*2);
		GPIOB->PUPDR |= (2U << 2*2);
	/*set pb3 as input */ // in keypad C3
		GPIOB->MODER &= ~(3U << 2*3);
		GPIOB->PUPDR |= (2U << 2*3);
	/*set pb4 as input */ // in keypad C4
		GPIOB->MODER &= ~(3U << 2*4);
		GPIOB->PUPDR |= (2U << 2*4);

	/* arrangement pb3 as interrupt*/
	    EXTI->RTSR1 |=(1U<<3);
	    EXTI->EXTICR[0] |= (1U<<8*3);
	    EXTI->IMR1 |=(1<<3);
	    NVIC_SetPriority(EXTI2_3_IRQn,0);
	    NVIC_EnableIRQ(EXTI2_3_IRQn);

    /* arrangement pb1 as interrupt*/
	    EXTI->RTSR1 |=(1U<<1);
	    EXTI->EXTICR[0] |= (1U<<8*1);
	    EXTI->IMR1 |=(1<<1);
	    NVIC_SetPriority(EXTI0_1_IRQn,1);
	    NVIC_EnableIRQ(EXTI0_1_IRQn);

	/* arrangement pb2 as interrupt*/
	    EXTI->RTSR1 |=(1U<<2);
	    EXTI->EXTICR[0] |= (1U<<8*2);
 	    EXTI->IMR1 |=(1<<2);
	    //NVIC_SetPriority(EXTI2_3_IRQn,1);
	    //NVIC_EnableIRQ(EXTI2_3_IRQn);

    /* arrangement pb4 as interrupt*/
	    EXTI->RTSR1 |=(1U<<4);
	    EXTI->EXTICR[1] |= (1U<<8*0);
	    EXTI->IMR1 |=(1<<4);
	    NVIC_SetPriority(EXTI4_15_IRQn,2);
	    NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void Delay(volatile uint32_t s) {
    for(; s>0; s--);
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

void printNumber(uint8_t b){
	USART2->TDR =(uint16_t)b;
	while(!(USART2->ISR&(1<<6)));
}

