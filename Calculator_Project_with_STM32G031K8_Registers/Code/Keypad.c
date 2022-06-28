/*
 * Keypad.c
 *
 *  Created on: 18 Ara 2020
 *      Author: ÖMER
 */

#include "stm32g0xx.h"
#include "Keypad.h"
#include "SSD.h"
#include "Process.h"
idle_flag =0;// if idle flag is zero, user never push the button,
 equal_check=0; // if equla_check is zero user dont't push '='(in keypad like that '#')
void Keypad_Library_Init(){
	System_Keypad_Output_Init();
	System_Keypad_Button_Init();
}

void System_Keypad_Output_Init(){
	 RCC->IOPENR |= (3U << 0); // GPIOA and GPIOB clock enable
	 GPIOA->MODER &=  ~(3U<<2*6); //pa6 as output ,in the keypad R1
	 GPIOA->MODER |=  (1U<<2*6);


	 GPIOA->MODER &=  ~(3U <<2*7); //pa7  as output ,in the keypad R2
	 GPIOA->MODER |=  (1 << 2*7);

	 GPIOA->MODER &=  ~(3U <<2*9); //pa9  as output ,in the keypad R3
	 GPIOA->MODER |=  (1 << 2*9);

	 GPIOA->MODER &=  ~(3U <<2*10); //pa10  as output ,in the keypad R4
	 GPIOA->MODER |=  (1 << 2*10);
}
void System_Keypad_Set(){
	GPIOA->ODR |= (1<<6);  //pa6 set,R1 set
	GPIOA->ODR |= (1<<7);  //pa7 set,R2 set
	GPIOA->ODR |= (1<<9);  //pa9 set,R3 set
	GPIOA->ODR |= (1<<10);  //pa10 set,R4 set

}
void System_Keypad_Reset(){
	GPIOA->ODR &=  ~(1U <<6); //pa6 reset,R1 reset
	GPIOA->ODR &=  ~(1U <<7); //pa7 reset,R2 reset
	GPIOA->ODR &=  ~(1U <<9); //pa9 reset,R3 reset
	GPIOA->ODR &=  ~(1U <<10);  //pa10 reset,R4 reset
}
void System_Keypad_Button_Init(){
	 RCC->IOPENR |= (3U << 0); // GPIOA and GPIOB clock enable
	/*set pb7 as input */ // in keypad C1
		GPIOB->MODER &= ~(3U << 2*7);
		GPIOB->PUPDR |= (2U << 2*7);
	/*set pb8 as input */ // in keypad C2
		GPIOB->MODER &= ~(3U << 2*8);
		GPIOB->PUPDR |= (2U << 2*8);
	/*set pb9 as input */ // in keypad C3
		GPIOB->MODER &= ~(3U << 2*9);
		GPIOB->PUPDR |= (2U << 2*9);
	/*set pa15 as input */ // in keypad C4
		GPIOA->MODER &= ~(3U << 2*15);
		GPIOA->PUPDR |= (2U << 2*15);

	/* arrangement pb7 as interrupt*/
	    EXTI->RTSR1 |=(1U<<7);
	    EXTI->EXTICR[1] |= (1U<<8*3);
	    EXTI->IMR1 |=(1<<7);
	    NVIC_SetPriority(EXTI4_15_IRQn,0);
	    NVIC_EnableIRQ(EXTI4_15_IRQn);

    /* arrangement pb8 as interrupt*/
	    EXTI->RTSR1 |=(1U<<8);
	    EXTI->EXTICR[2] |= (1U<<8*0);
	    EXTI->IMR1 |=(1<<8);
	    NVIC_SetPriority(EXTI4_15_IRQn,0);
	   	NVIC_EnableIRQ(EXTI4_15_IRQn);


	/* arrangement pb9 as interrupt*/
	    EXTI->RTSR1 |=(1U<<9);
	    EXTI->EXTICR[2] |= (1U<<8*1);
 	    EXTI->IMR1 |=(1<<9);
 	    NVIC_SetPriority(EXTI4_15_IRQn,0);
 	  	NVIC_EnableIRQ(EXTI4_15_IRQn);


    /* arrangement pa15 as interrupt*/
	    EXTI->RTSR1 |=(1U<<15);
	    //EXTI->EXTICR[1] |= (1U<<8*0);
	    EXTI->IMR1 |=(1<<15);
	    NVIC_SetPriority(EXTI4_15_IRQn,0);
	   	NVIC_EnableIRQ(EXTI4_15_IRQn);

}
void EXTI4_15_IRQHandler (){

	Delay(1000); // for bouncing
	idle_flag=idle_flag+1;// if user push the button,this is for timer interrupt
	Is_there_new_Operation=1;// it is send a message to ssd for display new number
	 // we have to reset this flag to clean ssd..
	// we have to reset these values for new operations
	//Scientific_Trigonometric_flag=0;
	//result_flag=0;


	System_Keypad_Reset();
	if((EXTI->RPR1>>7)&1){ // C1 Button is pressed (1,4,7,*)
		Process_C1_Check_Function();
		Scientific_Trigonometric_flag=0;
		result_flag=0;
		invalid_flag=0;
		EXTI->RPR1 |=(1<<7);
	}
	else if((EXTI->RPR1>>8)&1){  // c2 button is pressed (2,5,8,0)
		Process_C2_Check_Function();
		Scientific_Trigonometric_flag=0;
		result_flag=0;
		invalid_flag=0;
		EXTI->RPR1 |=(1<<8);
	}
	else if((EXTI->RPR1>>9)&1){// c3 button is pressed (3,6,9,#)
		Process_C3_Check_Function();
		Delay(1000);
		EXTI->RPR1 |=(1<<9);
	}

	else if((EXTI->RPR1>>15)&1){ // c4 button is pressed (a,b,c,d)
		Process_C4_Check_Function();
		Scientific_Trigonometric_flag=0;
		result_flag=0;
		invalid_flag=0;
		EXTI->RPR1 |=(1<<15);
		}

	System_Keypad_Set();
	Watchdog_Update();
}
























