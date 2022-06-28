/*
 * main.c
 *problem1
 * author: Omer Cebeci 171024007
 */

#include "stm32g0xx.h"
#include "System.h" // my system library
#include "stdio.h"

#define MPU6050_ADDRESS 0x68
#define MPU6050_WHO_AM_I 0x75
#define MPU6050_PWR_MGMT_1 0x6B

#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define EEPROM_ADDRESS 0xA2


#define   MpuPhysicalAdd  0x68
#define    WhoAmIReg  0x75

uint32_t b ;
double a ;


int main(void) {
	//System_Init(); // for all initializes
	UART_Init(9600);
	Init_I2C();
	uint8_t data[3];
	data[0]=0;
	data[1]=0;
	data[2]=4;
	 Multi_Write(EEPROM_ADDRESS,*data,3);
    while(1) {







    }

    return 0;
}
void delay(volatile uint32_t s) {
    for(; s>0; s--);
}

