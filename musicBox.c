/* ###################################################################
**     Filename    : main.c
**     Project     : kadai5
**     Processor   : MKL46Z256VLL4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-06-08, 14:21, # CodeGen: 0
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
#define REST 2147483647
#define TEMPO 45000
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/


	PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  int i=0,j=0,flag1=0,flag2=0;
  int sin[25] = {
		   0x80,0x9F,0xBD,0xD7,0xEC,
		   0xF9,0xFF,0xFD,0xF3,0xE2,
		   0xCB,0xAF,0x90,0x6F,0x50,
		   0x32,0x1D,0x0C,0x02,0x00,
		   0x06,0x13,0x28,0x42,0x60
  };
  // int melody[8]={611, 544, 485, 458, 408, 363, 323, 0};
  int kirakira[42]={611,611,408,408,363,363,408,
		  458,458,485,485,544,544,611,
		  408,408,458,458,485,485,544,
		  408,408,458,458,485,485,544,
		  611,611,408,408,363,363,408,
		  458,458,485,485,544,544,611
  };
  int kirakira_length[42]={
		  4,4,4,4,4,4,2,
		  4,4,4,4,4,4,2,
		  4,4,4,4,4,4,2,
		  4,4,4,4,4,4,2,
		  4,4,4,4,4,4,2,
		  4,4,4,4,4,4,2,
  };

  	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; // PTB �̃N���b�N��L���ɂ���
	PORTB_PCR0 = PORT_PCR_MUX(1); // PTB0 �� GPIO �ɐݒ肷��
	GPIOB_PDDR |= (1<<0); // PTB0 ���o�͂ɐݒ肷��
	PORTB_PCR1 = PORT_PCR_MUX(1); // PTB1 �� GPIO �ɐݒ肷��
	GPIOB_PDDR |= (1<<1); // PTB1 ���o�͂ɐݒ肷��
	PORTB_PCR2 = PORT_PCR_MUX(1); // PTB2 �� GPIO �ɐݒ肷��
	GPIOB_PDDR |= (1<<2); // PTB2 ���o�͂ɐݒ肷��
	PORTB_PCR3 = PORT_PCR_MUX(1); // PTB3 �� GPIO �ɐݒ肷��
	GPIOB_PDDR |= (1<<3); // PTB3 ���o�͂ɐݒ肷��

   SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK; // PTE �̃N���b�N��L���ɂ���
   PORTE_PCR0 = PORT_PCR_MUX(1); // PTE0 �� GPIO �ɐݒ肷��
   GPIOE_PDDR |= (1<<0); // PTE0 ���o�͂ɐݒ肷��
   PORTE_PCR1 = PORT_PCR_MUX(1); // PTE1 �� GPIO �ɐݒ肷��
   GPIOE_PDDR |= (1<<1); // PTE1 ���o�͂ɐݒ肷��
   PORTE_PCR2 = PORT_PCR_MUX(1); // PTE2 �� GPIO �ɐݒ肷��
   GPIOE_PDDR |= (1<<2); // PTE2 ���o�͂ɐݒ肷��
   PORTE_PCR3 = PORT_PCR_MUX(1); // PTE3 �� GPIO �ɐݒ肷��
   GPIOE_PDDR |= (1<<3); // PTE3 ���o�͂ɐݒ肷��
   PORTE_PCR31 = PORT_PCR_MUX(1); // PTE31 �� GPIO �ɐݒ肷��
   GPIOE_PDDR |= (0<<31); // PTE31 ����͂ɐݒ肷��
   PORTE_PCR19 = PORT_PCR_MUX(1); // PTE19 �� GPIO �ɐݒ肷��
   GPIOE_PDDR |= (0<<19); // PTE31 ����͂ɐݒ肷��





  /* For example: for(;;) { } */
   /*	����炷���߂̊��荞��	*/
   SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
   SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b11); // Set TPM clock to MCGIRCLK (p.206)
   MCG_C2 |= MCG_C2_IRCS_MASK; // Fast (4Mhz) IRC as clock source (p.386)
   MCG_SC &= ~MCG_SC_FCRDIV(0b111); // Set clock divider to 1, 0b000 (p.394)
   TPM0_SC = 0;
   TPM0_CNT = 0;
   TPM0_MOD = kirakira[0];
   TPM0_SC |= TPM_SC_PS(0b000);
   TPM0_SC |= TPM_SC_CMOD(0b01); // increment mode
   /*	���K�������邽�߂̊��荞��	*/
   SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
//   SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b11); // Set TPM clock to MCGIRCLK (p.206)
   TPM1_SC = 0;
   TPM1_CNT = 0;
   TPM1_MOD = TEMPO / kirakira_length[0];
   TPM1_SC |= TPM_SC_PS(0b000);		// // divided by 1
   TPM1_SC |= TPM_SC_CMOD(0b01); // increment mode

   SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;

   bool pte31_val, pte19_val;
   for(int i=0;i<1000000;i++);
   while(1){
	   pte31_val = GPIOE_PDIR&(1<<31) ? 1 : 0; // PTE31 �� 1 �Ȃ� 1�A0 �Ȃ� 0 ��Ԃ�
	   do{
		   pte31_val = GPIOE_PDIR&(1<<31) ? 1 : 0; // PTE31 �� 1 �Ȃ� 1�A0 �Ȃ� 0 ��Ԃ�
	   }while(!pte31_val);
	   do{
		   pte31_val = GPIOE_PDIR&(1<<31) ? 1 : 0; // PTE31 �� 1 �Ȃ� 1�A0 �Ȃ� 0 ��Ԃ�
	   }while(pte31_val);

	   pte19_val = GPIOE_PDIR&(1<<19) ? 1 : 0; // PTE31 �� 1 �Ȃ� 1�A0 �Ȃ� 0 ��Ԃ�
	   if(pte19_val == 1){
		   flag2 = 0;
	   }else{
		   flag2 = 1;
	   }

	   TPM1_SC |= TPM_SC_TOF_MASK;   // clock start
	   TPM0_SC |= TPM_SC_TOF_MASK;   // clock start

	   while(1){

		   pte31_val = GPIOE_PDIR&(1<<31) ? 1 : 0;
		   if(pte31_val){
			   flag1=1;
		   }else if(flag1 == 1 && pte31_val == 0){
			   break;
		   }

		   if((TPM1_SC & TPM_SC_TOF_MASK) == TPM_SC_TOF_MASK) {
			   TPM1_SC = 0;
			   TPM1_CNT = 0;
			   pte19_val = GPIOE_PDIR&(1<<19) ? 1 : 0;
			   if(flag2 == 0){
				   TPM1_MOD = TEMPO / kirakira_length[j];
			   }else{
				   TPM1_MOD = TEMPO / kirakira_length[j] / 2;
			   }

			   TPM1_SC |= TPM_SC_PS(0b000);
			   TPM1_SC |= TPM_SC_CMOD(0b01); // increment mode
			   TPM1_SC |= TPM_SC_TOF_MASK;   // clock start


			   TPM0_SC = 0;
			   TPM0_CNT = 0;
			   TPM0_MOD = kirakira[j];
			   TPM0_SC |= TPM_SC_PS(0b000);
			   TPM0_SC |= TPM_SC_CMOD(0b01); // increment mode
			   TPM0_SC |= TPM_SC_TOF_MASK;   // clock start


			   j = (j+1) % (sizeof(kirakira) / sizeof(int));


		   }

		   if ((TPM0_SC & TPM_SC_TOF_MASK) == TPM_SC_TOF_MASK) {
			   // ���荞�܂ꂽ�犄�荞�݃^�C�}�����Z�b�g���Ă����i�K�{!!�j
				TPM0_SC |= TPM_SC_TOF_MASK;
				// ���荞�܂ꂽ�ۂ̏���


				GPIOB_PCOR = (15<<0);
				GPIOE_PCOR = (15<<0);
				GPIOB_PSOR = (sin[i]>>4)& 0b1111;
				GPIOE_PSOR = sin[i]& 0b1111;
				i = (TPM0_MOD == REST) ? i :(i+1) % 25;
		   }
	   }
	   flag1=0;
	   j=0;
   }


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
