/*
 * main.c
 *This project include 3 different libraries:
 *1)Keypad: have functions like that Keypad initializes,interrupt
 *2)SSD:have functions like thatinitializes,set_ssd,display_numbers(this numbers can be nagative,positive, positive floating point format,negative floating point format)
 *3)Process:All other operations in this library,for example calculation operations,keypad_number_selection,or some initialize (timer,watchdog)
 *this calculator function have these operations types:
 *x+x
 *x-y
 *x+y
 *ln(x)
 *sin(x),cos(x),tan(x),cot(x),sin(x+y),cos(x+y),tan(x+y),cot(x+y) // variables numbers can increase for example (x y z f)
 *User can this operation -> first operation ln(x) and then second operation ln(ln(x)) or tan(ln(x)) // user can do any scientific operation after first operation
 *User can this operation -> first operation ln(x) and then second operation y+ln(x)  // user can do any normal operation after first operation
 *Also this code give a overflow signal like that(----),when -> result>9999 ,result<-999 ,x/0,  (ln(x) -> x<0)
 *User can use negative number
 *User can see numbers like that 1.23, -1.23 ,11.23,-11.2,111.2,1111.
 *there are a lot of flags for some controls for example if user want to enter negative number,or if result negative maybe
 *there are a lot of if-else statement because we have to check always a lot of things for example is number negative? or integer? or overflow?
 * author: Omer Cebeci 171024007
 */

#include "stm32g0xx.h"
#include "SSD.h"
#include "Keypad.h"
#include "Process.h"




void TIM3_IRQHandler(){// this timer is used idle mode,if user dont push anything into 10 seconds,ssd will close.
	if(timer<10){
		timer=timer+1;
	}
	TIM3->SR &=  ~(1U<<0);

}

int main(void) {
	result_old=0;
	System_Segment_Init(); // ssd initialize

	Keypad_Library_Init(); // keypad initialize

	Process_Init(); // timer initialize
	//Timer1_Init();
	//Delay(500);
	System_Decimal_Set();// ssd's decimal point is setted
	//Delay(500);
	//First_2_Last_2();
	//Delay(500);
	//TIM3->DIER=1;
	System_Keypad_Set();// R1 R2 R3 R4 are setted (in Keypad)
	while(idle_flag==0){ // for idle state if user dont push button along ten second,ssd reset.
		if(timer<10){
			Delay(50);
			First_2_Last_2();// first four digit my school number display
			Delay(50);
		}
		if(timer==10){// check the time,if ten secons happpen reset ssd
			Delay(50);
			SSD_Reset();
			Delay(50);
		}
		if(idle_flag==1){// if user push one button ,break the while and pass the calculation while...
			break;
		}
	}
	timer=0;
    while(1) {// calculation while

    		if(timer==10){ // if user dont push '=' (in keypad '#'),along ten seconds ssd display my school number...
    			Delay(50);
    			First_2_Last_2();// first four digit my school number display
    			Delay(50);
    			if(idle_flag!=1){// if user push one button ,break the while and pass the calculation while...
    						timer=11;
    					}
    		}
    		else {// if user push '=' (in keypad '#'),along ten seconds ,user can see results...
				double b ;
				int  tantitive_result ;
				result_old=result; //2.0 -2=0  2.24-2=0.24
				if(result_old>9999|| result_old<-999){ // this if statement for overflow.../ if there are a overflow situation,every flag will be zero ,only invalid flag set
					Scientific_Trigonometric_flag=0;// we reset all flag only invalid flag will set.
					result_flag=0;//reset
					invalid_flag=1;//set
					result_old=0;//reset
					result=0;//reset    // 2.24-  2=0.24
				}
				tantitive_result=(int)result_old;// tantitive result for find the floating number...
				if(Scientific_Trigonometric_flag==1){ // Number_array_check condition is for second operation,if Number_array_check is not equal zero we did same operation

						if(result_old-tantitive_result==0){ // number is normal number there is no floating point
										if(result_old>0){  // if result is positive
																Delay(50);
																Number_Find(result_old);
																Delay(50);
										 }
											else { // if result is negative
																 result_old=result_old*(-1);
																 Negatif_Number_Find((uint32_t)result_old);
																 result_old=result_old*(-1);
											}
						}
						else{// result-result_tantitive=> after dat   1.25-1=0.25
									if(result_old>0){// if result is bigger than zero
														b=result_old-tantitive_result;
														b=b*1000;
														//Delay(50);
														Floating_Display(tantitive_result,(b)); // first argument is before dat,second argument is after dat.
														//Delay(50);
									}
									else { // if result is less than zero
														b=result_old-tantitive_result;
														b=b*1000*(-1);
														Floating_Display_Negative(tantitive_result,b);
														b=b*(-1);
									}
						  }

				 }
				else if (result_flag==1){// if Number_array_check is equal zero,we will do next operation so we dont display result.

								if(result_old-tantitive_result==0){ // check for floating or not ?
										if(result_old>0){  // if result is positive
														//Delay(10);
														Number_Find(result_old);
														//Delay(10);
											 }
											 else { // if result is negative
														 result_old=result_old*(-1);
														 Negatif_Number_Find((uint32_t)result_old);
														 result_old=result_old*(-1);
											 }
								  }
								  else{
											if(result_old>0){// if result is bigger than zero
																b=result_old-tantitive_result;
																b=b*1000;
																Floating_Display(tantitive_result,(b)); // first argument is before dat,second argument is after dat.
											}
											else { // if result is less than zero
																b=result_old-tantitive_result;
																if(b<0)
																	b=b*1000*(-1);
																if(tantitive_result<0)
																	tantitive_result=tantitive_result*(-1);

																Floating_Display_Negative(tantitive_result,b);
																//b=b*(-1);
											 }
								   }

													}
			 else if (invalid_flag==1){// if Number_array_check is equal zero,we will do next operation so we dont display result.
												// Delay(50);
												 Display_zero();//----
												// Delay(50);
					  }
					 else if(Is_there_new_Operation=1){// if first operation finish and user want to do another operation,user will new number values at ssd...
												// Delay(50);

						 	 	 	 	 	 	 SSD_Number_Display();

												// Delay(50);
						}

			Watchdog_Update();

    }//for else
    }



    return 0;
}


