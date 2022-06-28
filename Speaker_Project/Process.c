/*
 * Process.c
 *
 *  Created on: 18 Ara 2020
 *      Author: ÖMER
 */

#include "stm32g0xx.h"

#include "Keypad.h"
#include "Process.h"
#include "System.h"

void Process_C1_Check_Function(){
	GPIOA->ODR |=(1<<12);  //R1 Check
	if((GPIOB->IDR>>7)&1){ // if it is true ,user push the one;
					i=440; //Set frequency 440Hz

	}
	else{
			GPIOA->ODR &=  ~(1U <<12);// user dont push '1' (R1)
			GPIOA->ODR |=(1<<7);  //R2 Check
			if((GPIOB->IDR>>7)&1){ // if it is true ,user push the '4';
				i=520;//Set frequency 520Hz
			}

			else {
				GPIOA->ODR &=  ~(1U <<7);// user dont push '4'	(R2)
				GPIOA->ODR |=(1<<9);  //R3 Check  PA4
				if((GPIOB->IDR>>7)&1){ // if it is true ,user push the '7';
					i=720;//Set frequency 720Hz
				}
				else{
					GPIOA->ODR &=  ~(1U <<9);// user dont push '7'	(PA4)
					GPIOA->ODR |=(1<<10);  //R4 Check
					if((GPIOB->IDR>>7)&1){ // if it is true ,user push the '*'; //rest
						i=0;  //Set frequency 0Hz (Silent mode)
					}

				}

		   }

	}
}
void Process_C2_Check_Function(){
	GPIOA->ODR |=(1<<12);  //R1 Check
	if((GPIOB->IDR>>8)&1){ // if it is true ,user push the '2';
		i=480;//Set frequency 480Hz
		}

	else{
			GPIOA->ODR &=  ~(1U <<12);// user dont push '2' (R1)
			GPIOA->ODR |=(1<<7);  //R2 Check
			if((GPIOB->IDR>>8)&1){ // if it is true ,user push the '5';
				i=640;//Set frequency 640Hz
			}

			else {
					GPIOA->ODR &=  ~(1U <<7);// user dont push '5'	(R2)
					GPIOA->ODR |=(1<<9);  //R3 Check  PA4
					if((GPIOB->IDR>>8)&1){ // if it is true ,user push the '8';
						i=760;//Set frequency 760Hz
					}

					else{
						GPIOA->ODR &=  ~(1U <<9);// user dont push '8'	(PA4)
						GPIOA->ODR |=(1<<10);  //R4 Check
						if((GPIOB->IDR>>8)&1){ // if it is true ,user push the '0';
							i=1640;//Set frequency 1640Hz
						}

					}

			}

		}
}
void Process_C3_Check_Function(){
	GPIOA->ODR |=(1<<12);  //R1 Check
	if((GPIOB->IDR>>9)&1){ // if it is true ,user push the '3';
		i=660;//Set frequency 660Hz
	}
	else{
			GPIOA->ODR &=  ~(1U <<12);// user dont push '3' (R1)
			GPIOA->ODR |=(1<<7);  //R2 Check
			if((GPIOB->IDR>>9)&1){ // if it is true ,user push the '6';
				i=680;//Set frequency 680Hz
			}

			else {
						GPIOA->ODR &=  ~(1U <<7);// user dont push '6'	(R2)
						GPIOA->ODR |=(1<<9);  //R3 Check  PA4
						if((GPIOB->IDR>>9)&1){ // if it is true ,user push the '9';
							i=800;//Set frequency 800Hz
						}
						else{
								GPIOA->ODR &=  ~(1U <<9);// user dont push '9'	(PA4)
								GPIOA->ODR |=(1<<10);  //R4 Check
								if((GPIOB->IDR>>9)&1){ // if it is true
									i=16000; // max value of frequency
								}

						}

			}

	}

}
void Process_C4_Check_Function(){
	GPIOA->ODR |=(1<<12);  //R1 Check
	if((GPIOA->IDR>>15)&1){ // if it is true ,user push the 'A'; //
			i=1000;//Set frequency 1000Hz
	}
	else{
			GPIOA->ODR &=  ~(1U <<12);// user dont push 'A' (R1)
			GPIOA->ODR |=(1<<7);  //R2 Check
			if((GPIOA->IDR>>15)&1){ // if it is true ,user push the 'B';
				i=2000;//Set frequency 2000Hz
			}
			else {
				GPIOA->ODR &=  ~(1U <<7);// user dont push 'B'	(R2)
				GPIOA->ODR |=(1<<9);  //R3 Check  PA4
				if((GPIOA->IDR>>15)&1){ // if it is true ,user push the 'C';
					i=3000;//Set frequency 3000Hz
				}
				else{
					GPIOA->ODR &=  ~(1U <<9);// user dont push 'C'	(PA4)
					GPIOA->ODR |=(1<<10);  //R4 Check
					if((GPIOA->IDR>>15)&1){ // if it is true ,user push the 'D';
						i=8000;//Set frequency 8000Hz
					}

				}

			}

		}


}


