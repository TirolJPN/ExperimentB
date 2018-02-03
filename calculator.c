/* ###################################################################
**     Filename    : main.c
**     Project     : kadai1
**     Processor   : MKL46Z256VLL4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-04-13, 13:44, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include <math.h>
/* User includes (#include below this line is not maintained by Processor Expert) */
int return_numbuf3(int *numbuf3, int num3){
	int i=0,j=0,digit=0;
	for(i=0,j=num3;j!=0;i++){
	   j /= 10;
	   digit++;
   }
   for(i=0;i<digit;i++){
	   numbuf3[i] = num3 % 10;
	   num3 /= 10;
   }
   return digit;
};

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	/* Write your code here */
	   //カウントの数

	int count=0;
	int numbuf1[2]={0,0};
	int num1=0;
	int numbuf2[2]={0,0};
	int num2=0;
	int numbuf3[4]={0,0,0,0};
	int num3=0;
	int numindex1=-1;
	int numindex2=-1;
	int numindex3=-1;
	int sign=-1;
	int flag=0;
	int i=0,j=0;
	int digit=0;
	double tmp;

	//count の２進数変換
	bool pta1_val;

	   SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; // PTA のクロックを有効にする
	   PORTA_PCR1 = PORT_PCR_MUX(1); // PTA1 を GPIO に設定する
	   GPIOA_PDDR |= (0<<1); // PTA1 を入力に設定する
	   //　出力にPTB0,1,2,3を使用
	   SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; // PTB のクロックを有効にする
	   PORTB_PCR0 = PORT_PCR_MUX(1); // PTB0 を GPIO に設定する
	   GPIOB_PDDR |= (1<<0); // PTB0 を出力に設定する
	   PORTB_PCR1 = PORT_PCR_MUX(1); // PTB1 を GPIO に設定する
	   GPIOB_PDDR |= (1<<1); // PTB1 を出力に設定する
	   PORTB_PCR2 = PORT_PCR_MUX(1); // PTB2 を GPIO に設定する
	   GPIOB_PDDR |= (1<<2); // PTB2 を出力に設定する
	   PORTB_PCR3 = PORT_PCR_MUX(1); // PTB3 を GPIO に設定する
	   GPIOB_PDDR |= (1<<3); // PTB3 を出力に設定する

	   //入力にPTA2,PTD3,PTA12,PTA4を使用、それぞれ上位4,3,2,1桁目
	   SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; // PTD のクロックを有効にする
	   PORTA_PCR2 = PORT_PCR_MUX(1); // PTA2 を GPIO に設定する
	   GPIOA_PDDR |= (1<<2); // PTA2 を出力に設定する
	   PORTD_PCR3 = PORT_PCR_MUX(1); // PTD3 を GPIO に設定する
	   GPIOD_PDDR |= (1<<3); // PTD3 を出力に設定する
	   PORTA_PCR12 = PORT_PCR_MUX(1); // PTA12 を GPIO に設定する
	   GPIOA_PDDR |= (1<<12); // PTA2 を出力に設定する
	   PORTA_PCR4 = PORT_PCR_MUX(1); // PTA4 を GPIO に設定する
	   GPIOA_PDDR |= (1<<4); // PTA4 を出力に設定する

	   //プッシュスイッチがOFFになるまで待つ
	   do{
		   pta1_val = GPIOA_PDIR&(1<<1) ? 1 : 0;
	   }while(pta1_val);
	   // LEDを消灯（初期状態）
	   GPIOB_PCOR = (15<<0);
	   GPIOB_PSOR = (15<<0);
	   while(1){
		   do{
			   pta1_val = GPIOA_PDIR&(1<<1) ? 1 : 0;
		   }while(!pta1_val);
		   do{
			   pta1_val = GPIOA_PDIR&(1<<1) ? 1 : 0;
		   }while(pta1_val);
		   // 入力をポートから読み込む
		   count =  (GPIOA_PDIR&(1<<2) ? 8 : 0)
					   +(GPIOD_PDIR&(1<<3) ? 4 : 0)
					   +(GPIOA_PDIR&(1<<12) ? 2 : 0)
					   +(GPIOA_PDIR&(1<<4) ? 1 : 0);
		   // 入力がFか?
		   if(count==15){
			   if(numindex2>=0){
				   if(flag == 0){
					   for(i=0;i <= numindex1; i++){
						    tmp= (double)numbuf1[i] * pow(10.0,(double)(numindex1-i));
						    num1 += (int)tmp;
					   }
					   for(i=0;i <= numindex2; i++){
						   tmp= (double)numbuf2[i] * pow(10.0,(double)(numindex2-i));
						   num2 += (int)tmp;
					   }
					   if(sign == 10){
						   num3 = num1 + num2;
						   digit = return_numbuf3(numbuf3, num3);
						   numindex3 = digit - 1;
						   flag = 1;
						   GPIOB_PCOR = (15<<0);
						   GPIOB_PSOR = (numbuf3[numindex3--]<<0);
					   }else if(sign == 11){
						   num3 = num1 - num2;
						   if(num3<0){
							   GPIOB_PCOR = (15<<0);
							   GPIOB_PSOR = (14<<0);
							   count=0,num1=0,num2=0,num3=0,numindex1=-1,numindex2=-1,numindex3=-1,sign=-1,flag=0,digit=0;
						   }else{
							   digit = return_numbuf3(numbuf3, num3);
							   numindex3 = digit - 1;
							   flag = 1;
							   GPIOB_PCOR = (15<<0);
							   GPIOB_PSOR = (numbuf3[numindex3--]<<0);
						   }
					   }else if(sign == 12){
						   num3 = num1 * num2;
						   digit = return_numbuf3(numbuf3, num3);
						   numindex3 = digit - 1;
						   flag = 1;
						   GPIOB_PCOR = (15<<0);
						   GPIOB_PSOR = (numbuf3[numindex3--]<<0);
					   }else if(sign == 13){
						   if(num2 == 0){
							   GPIOB_PCOR = (15<<0);
							   GPIOB_PSOR = (14<<0);
							   count=0,num1=0,num2=0,num3=0,numindex1=-1,numindex2=-1,numindex3=-1,sign=-1,flag=0,digit=0;
						   }else{
							   num3 = num1 / num2;
							   digit = return_numbuf3(numbuf3, num3);
							   numindex3 = digit - 1;
							   flag = 1;
							   GPIOB_PCOR = (15<<0);
							   GPIOB_PSOR = (numbuf3[numindex3--]<<0);
						   }
					   }
				   }else{
					   if(numindex3<0){
						   GPIOB_PCOR = (15<<0);
						   GPIOB_PSOR = (15<<0);
						   count=0,num1=0,num2=0,num3=0,numindex1=-1,numindex2=-1,numindex3=-1,sign=-1,flag=0,digit=0;
					   }else{
						   GPIOB_PCOR = (15<<0);
						   GPIOB_PSOR = (numbuf3[numindex3--]<<0);
					   }
				   }
			   }else{
				   GPIOB_PCOR = (15<<0);
				   GPIOB_PSOR = (14<<0);
			   }

		   //　入力が0~9か
		   }else if(0<=count && count<=9){
			   if(sign >= 10){
				   if(numindex2 >= -1 && numindex2 <= 0){
					   GPIOB_PCOR = (15<<0);
					   GPIOB_PSOR = (count<<0);
					   numbuf2[++numindex2] = count;
				   }else{
					   GPIOB_PCOR = (15<<0);
					   GPIOB_PSOR = (14<<0);
				   }
			   }else{
				   if(numindex1 >= -1 && numindex1 <= 0){
					   GPIOB_PCOR = (15<<0);
					   GPIOB_PSOR = (count<<0);
					   numbuf1[++numindex1] = count;
				   }else{
					   GPIOB_PCOR = (15<<0);
					   GPIOB_PSOR = (14<<0);
				   }
			   }
		   }else{
			   if(numindex1>=0 && numindex2 == -1 && sign ==-1){
				   GPIOB_PCOR = (15<<0);
				   GPIOB_PSOR = (count<<0);
				   sign = count;
			   }else{
				   GPIOB_PCOR = (15<<0);
				   GPIOB_PSOR = (14<<0);
			   }

		   }
	   }




  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/


/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
