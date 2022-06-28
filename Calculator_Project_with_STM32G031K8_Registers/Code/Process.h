/*
 * Process.h
 *
 *  Created on: 18 Ara 2020
 *      Author: ÖMER
 */

#ifndef PROCESS_H_
#define PROCESS_H_

int timer;
int operation_type ; // 1->addition,2->substraction,3->mul. ,4->division
int operation_place;// this values is used for calculation first and second number//// before operation_place,there is first number, after operation_place,there is second number
int flag_timer;
int key_flag; // if key_flag is equal 0, calculator expect first number,if key_flag is equal 1 ,calculator expect second number....
double result ; // result of the calculation
//double number_number[5];
double result_old; // for use the previous result
int result_flag ;
int Scientific_Trigonometric_flag;
int Is_there_new_Operation ;
typedef struct Number {
	double array_number[10];// this is our stored array ,all inputs come this array and then  numbers are created and operation_type is determined
}Number;
Number number;
int Number_array_check;//The number of presses is kept in this value
int invalid_flag;

void Timer1_Init();
void First_2_Last_2();
void Display_School_Number();// 4007
void System_Timer_Init();
void Process_Init();
void Watchdog_Init();
void Watchdog_Update();

void Process_Scientific_Trigonometric_Result();
void Process_C1_Check_Function();
void Process_C2_Check_Function() ;
void Process_C3_Check_Function();
void Process_C4_Check_Function();
void Process_Result();


void SSD_Number_Display();
#endif /* PROCESS_H_ */
