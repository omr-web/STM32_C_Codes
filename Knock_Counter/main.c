/*
 * main.c
 *
 * author: Omer Cebeci 171024007
 */

#include "stm32g0xx.h"
#include "System.h"
#include "stdio.h"

counter =0;
uint16_t check=0;  //if user read the ADC's value,this value is written to check if check is smaller than 229
/* if there is no sound voltage always constant (229) ,if there is sound voltage change (check<229)  */
int button_check =0;  // for checking the button


int main(void) {
	System_Init();
	uint16_t data ;

    while(1) {
    	data= ADC_Data();
    	printf(" %d ",data);
    	//Display_zero();
    	button_check=System_Button_read();
    		    		if(button_check==1){ // if user push the button,counter =0 ,ssd display 0 ;
    		    			counter=0;
    		    			Delay(300);
    		    		}

    		    		else{
    		    		check =ADC_Data();
    		    		if(check<229)// check the microphone,if there is a sound counter++;
    		    			counter=counter+1;
    		    		}

    		    	Number_Find(counter);// Display ssd
    }

    return 0;
}

