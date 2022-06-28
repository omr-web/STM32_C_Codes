/*
 * main.c
 *this code was written to set different frequency for speaker.When user push the button,related interrupt work and new frequency is set.Also SSD display frequency all the time...
 * author: Omer Cebeci 171024007
 */

#include "stm32g0xx.h"
#include "System.h"
#include "Keypad.h"
#include  "Process.h"
#include "SSD.h"


int main(void) {
	/*All initializes */
	System_Init();
	Keypad_Library_Init();
	System_Keypad_Set();
	System_Segment_Init();
    while(1) {

    	Delay(200);
    	Number_Find(i); // Display frequency
    	Delay(200);

    }

    return 0;
}


