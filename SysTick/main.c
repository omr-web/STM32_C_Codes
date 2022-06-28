/*
 * main.c
 *
 * author: Omer Cebeci 171024007
 */

#include "stm32g0xx.h"
#include "System.h" // my system library




int main(void) {
	System_Init(); // for all initializes

    while(1) {
    	System_LED_Set();  // set led
    	Delay_ms(2);  // systick delay
    	System_LED_Reset();  // reset led
    	Delay_ms(2);  // systick delay
    }

    return 0;
}

