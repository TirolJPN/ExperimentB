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
	   //�J�E���g�̐�

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

	//count �̂Q�i���ϊ�
	bool pta1_val;

	   SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; // PTA �̃N���b�N��L���ɂ���
	   PORTA_PCR1 = PORT_PCR_MUX(1); // PTA1 �� GPIO �ɐݒ肷��
	   GPIOA_PDDR |= (0<<1); // PTA1 ����͂ɐݒ肷��
	   //�@�o�͂�PTB0,1,2,3���g�p
	   SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; // PTB �̃N���b�N��L���ɂ���
	   PORTB_PCR0 = PORT_PCR_MUX(1); // PTB0 �� GPIO �ɐݒ肷��
	   GPIOB_PDDR |= (1<<0); // PTB0 ���o�͂ɐݒ肷��
	   PORTB_PCR1 = PORT_PCR_MUX(1); // PTB1 �� GPIO �ɐݒ肷��
	   GPIOB_PDDR |= (1<<1); // PTB1 ���o�͂ɐݒ肷��
	   PORTB_PCR2 = PORT_PCR_MUX(1); // PTB2 �� GPIO �ɐݒ肷��
	   GPIOB_PDDR |= (1<<2); // PTB2 ���o�͂ɐݒ肷��
	   PORTB_PCR3 = PORT_PCR_MUX(1); // PTB3 �� GPIO �ɐݒ肷��
	   GPIOB_PDDR |= (1<<3); // PTB3 ���o�͂ɐݒ肷��

	   //���͂�PTA2,PTD3,PTA12,PTA4���g�p�A���ꂼ����4,3,2,1����
	   SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; // PTD �̃N���b�N��L���ɂ���
	   PORTA_PCR2 = PORT_PCR_MUX(1); // PTA2 �� GPIO �ɐݒ肷��
	   GPIOA_PDDR |= (1<<2); // PTA2 ���o�͂ɐݒ肷��
	   PORTD_PCR3 = PORT_PCR_MUX(1); // PTD3 �� GPIO �ɐݒ肷��
	   GPIOD_PDDR |= (1<<3); // PTD3 ���o�͂ɐݒ肷��
	   PORTA_PCR12 = PORT_PCR_MUX(1); // PTA12 �� GPIO �ɐݒ肷��
	   GPIOA_PDDR |= (1<<12); // PTA2 ���o�͂ɐݒ肷��
	   PORTA_PCR4 = PORT_PCR_MUX(1); // PTA4 �� GPIO �ɐݒ肷��
	   GPIOA_PDDR |= (1<<4); // PTA4 ���o�͂ɐݒ肷��

	   //�v�b�V���X�C�b�`��OFF�ɂȂ�܂ő҂�
	   do{
		   pta1_val = GPIOA_PDIR&(1<<1) ? 1 : 0;
	   }while(pta1_val);
	   // LED�������i������ԁj
	   GPIOB_PCOR = (15<<0);
	   GPIOB_PSOR = (15<<0);
	   while(1){
		   do{
			   pta1_val = GPIOA_PDIR&(1<<1) ? 1 : 0;
		   }while(!pta1_val);
		   do{
			   pta1_val = GPIOA_PDIR&(1<<1) ? 1 : 0;
		   }while(pta1_val);
		   // ���͂��|�[�g����ǂݍ���
		   count =  (GPIOA_PDIR&(1<<2) ? 8 : 0)
					   +(GPIOD_PDIR&(1<<3) ? 4 : 0)
					   +(GPIOA_PDIR&(1<<12) ? 2 : 0)
					   +(GPIOA_PDIR&(1<<4) ? 1 : 0);
		   // ���͂�F��?
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

		   //�@���͂�0~9��
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
