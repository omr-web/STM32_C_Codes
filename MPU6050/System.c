/*
 * System.c
 *
 *  Created on: 5 Ara 2020
 *      Author: ÖMER
 */

#include "stm32g0xx.h"
#include "system.h"




uint32_t counter=0;
uint8_t data_old=0;





void System_Init(){

    System_LED_Init();
	System_Button_Init();

}

void System_LED_Init(){
	 /* Enable GPIOB and GPIOA clock */
	    RCC->IOPENR |= (3U << 0);
	 /* Setup PA0 as output */
	    GPIOA->MODER |=(1U<<0); // GPIOA_MODER first bit is equal to 1
	    GPIOA->MODER &=  ~(1U<<1);// GPIOA_MODER second bit is equal to 0

	    GPIOA->BRR |=(1<<0);
}
void System_LED_Toggle(){
	GPIOA->ODR ^=(1<<0);
}

void System_LED_Set(){
	GPIOA->ODR |=(1<<0); // GPIOA'ODR first bit is 1
}
void System_LED_Reset(){
	GPIOA->ODR &=  ~(1U<<0); // GPIOA's ODR first bit is 0
}

void System_Button_Init(){
	/* Enable GPIOB and GPIOA clock */
	    RCC->IOPENR |= (3U << 0);
    /*set pb7 as input */
	    GPIOB->MODER &= ~(3U << 2*7);
}
void USART2_IRQHandler (){
	uint8_t data= (uint8_t)USART2->RDR;

	printchar(data);
}

void uart_tx ( uint8_t c){


	if(c!=0){
		USART2->TDR =(uint16_t)c;

		//printchar(c); // c basacak
		data_old=c;
	}





}

uint8_t uart_rx(void){
	uint8_t data= (uint8_t)USART2->RDR;


	if(data_old!=data)
		return data ;
	else
		return 0 ;




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

void I2C1_IRQHandler(){

}
int _write(int fd,char *ptr,int len){
	(void)fd;
	for(int i=0;i<len;++i){
		printchar(ptr[i]);
	}
	return len;
}
void print(char *buf){
	int len=0;
	while(buf[len++]!= '\0'); // to find length of the buf
	_write(0,buf,len);
}
void printchar(uint8_t c){
	USART2->TDR =(uint16_t)c;
	while(!(USART2->ISR&(1<<6)));
}

int System_Button_read(){
	if((GPIOB->IDR>>7)&1){
		return 1;
	}
	else
		return 0 ;
}

////////////////////////////////
////////////////////////////single data transfer
uint8_t ReadI2C (uint8_t DeviceAdd, uint8_t RegisterAdd)
{

    uint8_t ReadedData = 0;
    // Write operation
    I2C1->CR2 = 0;
    I2C1->CR2 |= ((uint32_t)DeviceAdd << 1);
    I2C1->CR2 |= (1U << 16);
    I2C1->CR2 |= (1U << 13);
    while(!(I2C1->ISR & (1 << 1)));  // txis



    I2C1->TXDR = (uint32_t)RegisterAdd;
    while(!(I2C1->ISR & (1U << 6)));


    //read operation
    I2C1->CR2 = 0;
    I2C1->CR2 |= ((uint32_t)DeviceAdd << 1);//
    I2C1->CR2 |= (1U << 10);//read mode
    I2C1->CR2 |= (1U << 16);// number of bytes
    I2C1->CR2 |= (1U << 15);// NACK
    I2C1->CR2 |= (1U << 25);// Autoend



    I2C1->CR2 |= (1U << 13);
    while(!(I2C1->ISR & (1U << 2)));



    ReadedData = (uint8_t)I2C1->RXDR;



    return ReadedData;
}

void write_I2C(uint8_t DeviceAdd, uint8_t RegisterAdd,uint8_t data){
	 // Write operation
	 I2C1->CR2 = 0;
	 I2C1->CR2 |= ((uint32_t)DeviceAdd << 1);//slave address
	 I2C1->CR2 |= (2U << 16);//number of byte
	 I2C1->CR2 |= (1U << 13);//AUTOEND
	 while(!(I2C1->ISR & (1 << 1)));//txıs
	 I2C1->TXDR = (uint32_t)RegisterAdd;

	while(!(I2C1->ISR&(1<<1))); //TXİS
	I2C1->TXDR = (uint32_t)data;

}

//////////////////////////////////////////////////////
////////////////////multi data transfer
void Multi_ReadI2C (uint8_t DeviceAdd, uint8_t RegisterAdd,uint8_t* data,uint32_t num)
{

    // Write operation
    I2C1->CR2 = 0;
    I2C1->CR2 |= ((uint32_t)DeviceAdd << 1);
    I2C1->CR2 |= (1U << 16);
    I2C1->CR2 |= (1U << 13);
    while(!(I2C1->ISR & (1 << 1)));  // txis



    I2C1->TXDR = (uint32_t)RegisterAdd;
    while(!(I2C1->ISR & (1U << 6)));


    //read operation
    I2C1->CR2 = 0;
    I2C1->CR2 |= ((uint32_t)DeviceAdd << 1);
    I2C1->CR2 |= (1U << 10);//read mode
    I2C1->CR2 |= (num << 16);// number of bytes
    I2C1->CR2 |= (1U << 15);// NACK
    I2C1->CR2 |= (1U << 25);// Autoend
    I2C1->CR2 |= (1U << 13);

    for(int i=0;i<num;i++){
    	while(!(I2C1->ISR & (1U << 2)));
    	data[i]=(uint8_t)I2C1->RXDR;

    }
}

void Multi_Write(uint8_t DeviceAdd, uint8_t* data, uint32_t num){
		 I2C1->CR2 = 0;
		 I2C1->CR2 |= ((uint32_t)DeviceAdd << 1);//slave address
		 I2C1->CR2 |= (num << 16);//number of byte
		 I2C1->CR2 |= (1U<<25); //autoend
		 I2C1->CR2 |= (1U << 13);//generate start

		for(int i=0;i<num;i++){
			while(!(I2C1->ISR&(1<<1))); //TXİS
			I2C1->TXDR =data[i];
		}

}

void Init_I2C (void)
{
    RCC->IOPENR |= (1U << 1);



    // PB8 - PB9 GPIO Alternate Function I2C pins
    GPIOB->MODER &= ~(3U << 2*8);
    GPIOB->MODER |= (2 << 2*8);
    GPIOB->OTYPER |= (1U << 8);
    // AFX selection
    GPIOB->AFR[1] &= ~(0xFU << 4*0);
    GPIOB->AFR[1] |= (6U << 4*0);



    GPIOB->MODER &= ~(3U << 2*9);
    GPIOB->MODER |= (2U << 2*9);
    GPIOB->OTYPER |= (1U << 9);
    // AFX selection
    GPIOB->AFR[1] &= ~(0xFU << 4*1);
    GPIOB->AFR[1] |= (6U << 4*1);



    // Enable I2C1
    RCC->APBENR1 |= (1U << 21);



    I2C1->CR1 = 0;
    I2C1->CR1 |= (1U << 7);



    I2C1->TIMINGR |= (3U << 28);
    I2C1->TIMINGR |= (0x13U << 0);
    I2C1->TIMINGR |= (0xFU << 8);
    I2C1->TIMINGR |= (0x2U << 16);
    I2C1->TIMINGR |= (0x4U << 20);



    I2C1->CR1 |= (1U << 0);



    NVIC_SetPriority(I2C1_IRQn, 1);
    NVIC_EnableIRQ(I2C1_IRQn);
}
