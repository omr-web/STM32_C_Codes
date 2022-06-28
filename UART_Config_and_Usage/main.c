/*
 * main.c
 *problem1
 * author: Omer Cebeci 171024007
 */

#include "stm32g0xx.h"
#include "System.h" // my system library
#include "stdio.h"



int main(void) {
	//System_Init(); // for all initializes
	UART_Init(9600);
    while(1) {

    	//uart_tx(uart_rx()); // echo


    	printf("hellow");
    	//Delay_ms(20);
    }

    return 0;
}

