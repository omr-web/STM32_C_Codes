/*
 * Process.c
 *
 *  Created on: 18 Ara 2020
 *      Author: ÖMER
 */

#include "stm32g0xx.h"
#include "SSD.h"
#include "Keypad.h"
#include "Process.h"
#include "math.h"

timer=0;
int operation_place =0 ;operation_type; // 1->addition,2->substraction,3->mul. ,4->division
int flag_timer =0;
int key_flag=0; // if key_flag is equal 0, calculator expect first number,if key_flag is equal 1 ,calculator expect second number....
// result of the calculation,I dont give first value for result....
 result_flag=0 ;
Scientific_Trigonometric_flag=0;
double number_number[5];
invalid_flag=0; // if operation is invalid,invalid_flag would be 1, for example (3/0) or sqrt(-2)
Is_there_new_Operation=1;
int Number_array_check =0;

void Process_Init(){
	//SystemCoreClockUpdate();
	System_Timer_Init();
	//Timer1_Init();
	//Watchdog_Init();
	//SysTick_Config(SystemCoreClock/1000);
}
void Timer1_Init(){
	RCC->APBENR2 |=(1u<<11);
	TIM1->CR1=0;
	TIM1->CR1 |= (1<<7);
	TIM1->CNT =0;
	TIM1->PSC =999; // every  one second
	TIM1->ARR=(16000);
	TIM1->DIER |=(1<<0);
	TIM1->CR1 =0;
	NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,0);
	NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
}


void System_Timer_Init(){ // Timer3 initialize
		RCC->APBENR1 |=(1U<<1);
		TIM3->CR1=0;
		TIM3->CR1 |=(1<<7);
		TIM3->CNT =0;
		TIM3->PSC=999;  // old value 0
		TIM3->ARR=(16000); // less than 1 second  // old value 8000
		TIM3->DIER |=(1<<0);
		TIM3->CR1 |= (1<<0);
		NVIC_SetPriority(TIM3_IRQn,2);
		NVIC_EnableIRQ(TIM3_IRQn);

}
void Watchdog_Update(){
	IWDG->KR=0xAAAA;
}
void Watchdog_Init(){
	IWDG->KR=0x5555;
	IWDG->PR=1;
	//IWDG->RLR=0xFFF;
	//IWDG->WINR=0x0;
	IWDG->KR=0xCCCC;
}


void SysTick_Handler(){
	if(result_flag==1){
		    		   Number_Find(result);
		    	}
		    	else{
		    		    Delay(50);
		    		    SSD_Number_Display();
		    		    Delay(50);

		    	}

}
void First_2_Last_2(){ // this function display 1707

		Delay(500);
		System_D1();
		Display_Number(1);

		Delay(500);
		System_D2();
		Display_Number(7);

		Delay(500);
		System_D3();
		Display_Number(0);

		Delay(500);
		System_D4();
		Display_Number(7);



}
void Display_School_Number(){// this function display 4007
	for(int i=0;i<500;i++){
			Delay(500);
			System_D1();
			Display_Number(4);

			Delay(500);
			System_D2();
			Display_Number(0);

			Delay(500);
			System_D3();
			Display_Number(0);

			Delay(500);
			System_D4();
			Display_Number(7);

		}
}
void Process_C1_Check_Function(){
	GPIOA->ODR |=(1<<6);  //R1 Check
	if((GPIOB->IDR>>7)&1){ // if it is true ,user push the one;
					number.array_number[Number_array_check]=1;
					Number_array_check=Number_array_check+1;

	}
	else{
			GPIOA->ODR &=  ~(1U <<6);// user dont push '1' (R1)
			GPIOA->ODR |=(1<<7);  //R2 Check
			if((GPIOB->IDR>>7)&1){ // if it is true ,user push the '4';
				number.array_number[Number_array_check]=4;
				Number_array_check=Number_array_check+1;


			}

			else {
				GPIOA->ODR &=  ~(1U <<7);// user dont push '4'	(R2)
				GPIOA->ODR |=(1<<9);  //R3 Check  PA4
				if((GPIOB->IDR>>7)&1){ // if it is true ,user push the '7';
					number.array_number[Number_array_check]=7;
					Number_array_check=Number_array_check+1;

				}
				else{
					GPIOA->ODR &=  ~(1U <<9);// user dont push '7'	(PA4)
					GPIOA->ODR |=(1<<10);  //R4 Check
					if((GPIOB->IDR>>7)&1){ // if it is true ,user push the '*'; // this is 'E' for scientific mode
						number.array_number[Number_array_check]=15;
						Number_array_check=Number_array_check+1;
					}

				}

		   }

	}
}
void Process_C2_Check_Function(){
	GPIOA->ODR |=(1<<6);  //R1 Check
	if((GPIOB->IDR>>8)&1){ // if it is true ,user push the '2';
		number.array_number[Number_array_check]=2;
		Number_array_check=Number_array_check+1;

		}

	else{
			GPIOA->ODR &=  ~(1U <<6);// user dont push '2' (R1)
			GPIOA->ODR |=(1<<7);  //R2 Check
			if((GPIOB->IDR>>8)&1){ // if it is true ,user push the '5';
				number.array_number[Number_array_check]=5;
				Number_array_check=Number_array_check+1;

			}

			else {
					GPIOA->ODR &=  ~(1U <<7);// user dont push '5'	(R2)
					GPIOA->ODR |=(1<<9);  //R3 Check  PA4
					if((GPIOB->IDR>>8)&1){ // if it is true ,user push the '8';
						number.array_number[Number_array_check]=8;
						Number_array_check=Number_array_check+1;

					}

					else{
						GPIOA->ODR &=  ~(1U <<9);// user dont push '8'	(PA4)
						GPIOA->ODR |=(1<<10);  //R4 Check
						if((GPIOB->IDR>>8)&1){ // if it is true ,user push the '0';
							number.array_number[Number_array_check]=0;
							Number_array_check=Number_array_check+1;

						}

					}

			}

		}
}
void Process_C3_Check_Function(){
	GPIOA->ODR |=(1<<6);  //R1 Check
	if((GPIOB->IDR>>9)&1){ // if it is true ,user push the '3';
		number.array_number[Number_array_check]=3;
		Number_array_check=Number_array_check+1;


	}
	else{
			GPIOA->ODR &=  ~(1U <<6);// user dont push '3' (R1)
			GPIOA->ODR |=(1<<7);  //R2 Check
			if((GPIOB->IDR>>9)&1){ // if it is true ,user push the '6';
				number.array_number[Number_array_check]=6;
				Number_array_check=Number_array_check+1;

			}

			else {
						GPIOA->ODR &=  ~(1U <<7);// user dont push '6'	(R2)
						GPIOA->ODR |=(1<<9);  //R3 Check  PA4
						if((GPIOB->IDR>>9)&1){ // if it is true ,user push the '9';
							number.array_number[Number_array_check]=9;
							Number_array_check=Number_array_check+1;

						}
						else{
								GPIOA->ODR &=  ~(1U <<9);// user dont push '9'	(PA4)
								GPIOA->ODR |=(1<<10);  //R4 Check
								if((GPIOB->IDR>>9)&1){ // if it is true ,user push the '#'; // for '='
									Process_Result();  // later we will add mode variable for scientific ...

									timer=11;// if user push '=' (in kaypad '#')
								}

						}

			}

	}

}
void Process_C4_Check_Function(){
	GPIOA->ODR |=(1<<6);  //R1 Check
	if((GPIOA->IDR>>15)&1){ // if it is true ,user push the 'A'; // addition
			number.array_number[Number_array_check]=11;
			Number_array_check=Number_array_check+1;
	}
	else{
			GPIOA->ODR &=  ~(1U <<6);// user dont push 'A' (R1)
			GPIOA->ODR |=(1<<7);  //R2 Check
			if((GPIOA->IDR>>15)&1){ // if it is true ,user push the 'B'; //substraction
				number.array_number[Number_array_check]=12;
				Number_array_check=Number_array_check+1;
			}
			else {
				GPIOA->ODR &=  ~(1U <<7);// user dont push 'B'	(R2)
				GPIOA->ODR |=(1<<9);  //R3 Check  PA4
				if((GPIOA->IDR>>15)&1){ // if it is true ,user push the 'C'; // multiplicatiıon
					number.array_number[Number_array_check]=13;
					Number_array_check=Number_array_check+1;
				}
				else{
					GPIOA->ODR &=  ~(1U <<9);// user dont push 'C'	(PA4)
					GPIOA->ODR |=(1<<10);  //R4 Check
					if((GPIOA->IDR>>15)&1){ // if it is true ,user push the 'D'; // division
						number.array_number[Number_array_check]=14;
						Number_array_check=Number_array_check+1;
					}

				}

			}

		}


}

void Process_Result(){   // 1 2 11 3 4  =46  11
	Is_there_new_Operation=0;
	result=0;
	int i =0;
	//first number is found // 1 2 opetaitontype 2 3 #   2+2+2 2+2=4 +2 =6
	for(int i=0;i<10;i++){
		if((number.array_number[i]==11)||(number.array_number[i]==12)||(number.array_number[i]==13)||(number.array_number[i]==14)||(number.array_number[i]==15)){
			if(i==0 && number.array_number[0]==15 &&((number.array_number[1]!=11)&(number.array_number[1]!=12)&(number.array_number[1]!=13)&(number.array_number[1]!=14)&(number.array_number[1]!=15))){
							operation_place=operation_place+1;// ignore This if for 1+2=3 and + 5 = 8
						}
			else if(number.array_number[0]==15&&((number.array_number[1]==11)||(number.array_number[1]==12)||(number.array_number[1]==13)||(number.array_number[1]==14))){
				// this else if for 1+2 =3 and then second operation  ln(3)
				operation_place=operation_place+2; // because 15 11 (2)  15 and 11 is not a number value
				operation_type=15; // E '*'
				break ;
			}

						else{
						operation_type=number.array_number[i];
						break;
						}

		}
		else
			operation_place=operation_place+1;

	}

	if(operation_type==15){// For scientific calculations. if operations type is equla 15,user push the button 'E'
		Scientific_Trigonometric_flag=1;

	}
	if(operation_place==0){ // if this condition is true,we have to use previous result
			number_number[0]=result_old;// new first number is old result.
	}

	else{// if this condition is not true,we have to produce new number...
		if(number.array_number[0]==15){// if this condition is true ,negative number will come
			for(i =1;i<operation_place;i++){
								number_number[0]=number_number[0]+pow(10,i-1)*number.array_number[operation_place-i]*(-1);
			}
		}
		else

		for(i =0;i<operation_place;i++){
					number_number[0]=number_number[0]+pow(10,i)*number.array_number[operation_place-i-1];
		}


	}
	for(int l=0;l<operation_place;l++){// if user push the EEE thats means is pi
			if(number.array_number[l]==15&&number.array_number[i+1]==15&&number.array_number[l+2]==15)
				number_number[0]=3.14;
		}

	//Second number is found
	int j =0;
	for(int i =(operation_place+1);i<10;i++){ // we find ,how many number after operation place,these numbers comprise our second number
		if(number.array_number[i]==0)
			break;
		else
			j=j+1;
	}
	int m=0;
	for(int k=(j+operation_place) ; k>operation_place; --k){
			number_number[1]=number_number[1]+pow(10,(m))*number.array_number[k];
			m=m+1;
		}
	for(int l=operation_place;l<10;l++){// if user push the EEE thats means is pi (this is for second number)
				if(number.array_number[l]==15&&number.array_number[i+1]==15&&number.array_number[l+2]==15)
					number_number[1]=3.14;
			}

	switch (operation_type){// in this switch we select an operation type...
			case 11:// for addition
				for(int i=0;i<5;i++){
					result=result+number_number[i];
				}
			break;

			case 12: // substraction
				result =number_number[0]-number_number[1];

			break ;

			case 13://(*)
				result =number_number[0]*number_number[1];
			break ;

			case 14: // (/) division
				if(number_number[1]==0)
					invalid_flag=1;
				result=number_number[0]/number_number[1];
			break ;
	}
	if(Scientific_Trigonometric_flag==1){ // for scientific operations
		Process_Scientific_Trigonometric_Result();// if user push relevent buttons,pc go to the this function for other operations(log,ln,sin,cos,tan,cot)
	}
	else if(invalid_flag==0)// if operation is invalid this flag set for display '----'
		result_flag=1; // for normal operations
// for next calculation
Number_array_check=0;
for(int i =0;i<10;i++)
	number.array_number[i]=0;

number_number[0]=0;
number_number[1]=0;
operation_place=0;
operation_type=0;

///////////
}
void Process_Scientific_Trigonometric_Result(){
	int i =0;
	int j=0;
	number_number[0]=0,number_number[1]=0 ; // clear the numbers in stored array

	for( i =0;i<10;i++){
		if(number.array_number[i]==15&&number.array_number[i+1]==11){// EA for log
			operation_type= 26 ; // 15+11
			break ;
		}
		else if (number.array_number[i]==15 && number.array_number[i+1]==12){ // EB for ln
			operation_type= 27 ; // 15+12
			break ;
		}

		else if (number.array_number[i]==15 && number.array_number[i+1]==13){// EC for sqrt
			operation_type= 28 ; // 15+13
			break ;
		}
		else if (number.array_number[i]==15 && number.array_number[i+1]==14){// ED for x^2
					operation_type= 29 ; // 15+14
					break ;
				}
		else if (number.array_number[i]==15&&number.array_number[i+1]==15){ // trigonometric mode
			if(number.array_number[i+2]==11){ // sinus
				operation_type= 41 ; // 15+15+11
				break ;
			}
			else if(number.array_number[i+2]==12){// cosinus
				operation_type= 42 ; // 15+15+12
				break ;
			}
			else if(number.array_number[i+2]==13){ //tan
				operation_type= 43 ; // 15+15+13
				break ;
			}
			else if (number.array_number[i+2]==14){ // cot
				operation_type= 44 ; // 15+15+14
				break ;
			}
		}
	}

	if(number.array_number[0]==15 && ((number.array_number[1]!=11)&(number.array_number[1]!=12)&(number.array_number[1]!=13)&(number.array_number[1]!=14))){// if this condition is true ,negative number will come
				for(i =1;i<operation_place;i++){
									number_number[0]=number_number[0]+pow(10,i-1)*number.array_number[operation_place-i]*(-1);
				}
			}
	else if (number.array_number[0]==15 && ((number.array_number[1]==11)||(number.array_number[1]==12)||(number.array_number[1]==13)||(number.array_number[1]==14))){
		// this statement for 1+2=3 and then ln(3)
		number_number[0]=result_old;
	}
			else// this statement for 1+2 and then A BC D that means 3+x ,3-x,3/5,3*3

			for(i =0;i<operation_place;i++){
						number_number[0]=number_number[0]+pow(10,i)*number.array_number[operation_place-i-1];
			}
	switch (operation_type){
				case 26:
					result=(double)log10(number_number[0]);
					break;
				case 27:
					result=(double)log(number_number[0]);
					break ;
				case 28:
					if(number_number[0]<0){
						invalid_flag=1;
						Scientific_Trigonometric_flag=0;
						break;
					}
					else{
						result=(double)sqrt(number_number[0]);
						break ;
					}
				case 29:
					result=number_number[0]*number_number[0];
					break ;
				case 41:
					result=(double)sin((number_number[0])*3.14/180);
					break ;
				case 42:
					result=(double)cos((number_number[0])*3.14/180);
					break ;
				case 43:
					result=(double)tan((number_number[0])*3.14/180);
					break ;
				case 44:
					result=(double)(1/(tan((number_number[0])*3.14/180)));
					break ;
		}



}

void SSD_Number_Display(){
	if(Number_array_check==1){// if number_array_check is equal zero first number come,so we should write digit one
		Delay(100);
		System_D4();
		Display_Number(number.array_number[0]);// if number_array_check is equal zero,only first of array have number.

	}
	else if (Number_array_check==2){
		Delay(100);
		System_D3();
		Display_Number(number.array_number[0]);

		Delay(100);
		System_D4();
		Display_Number(number.array_number[1]);

	}
	else if(Number_array_check==3){
		Delay(100);
		System_D2();
		Display_Number(number.array_number[0]);

		Delay(100);
		System_D3();
		Display_Number(number.array_number[1]);

		Delay(100);
		System_D4();
		Display_Number(number.array_number[2]);
	}
	else if(Number_array_check==4){
		Delay(100);
		System_D1();
		Display_Number(number.array_number[0]);

		Delay(100);
		System_D2();
		Display_Number(number.array_number[1]);

		Delay(100);
		System_D3();
		Display_Number(number.array_number[2]);

		Delay(100);
		System_D4();
		Display_Number(number.array_number[3]);

	}
}



