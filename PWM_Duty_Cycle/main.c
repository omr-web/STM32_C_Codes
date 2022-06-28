/*
 * main.c
 *
 * author: Omer Cebeci 171024007
 */

#include "stm32g0xx.h"
#include "System.h"





int main(void) {
	System_Init();

	System_Keypad_Set();
    while(1) {


    }

    return 0;
}


