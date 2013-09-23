/* ###################################################################
 **     Filename    : ProcessorExpert.c
 **     Project     : semg_mkl15z128vlh4
 **     Processor   : MKL15Z128VLH4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2013-07-11, 23:27, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 **     Mail        : pzdongdong@163.com
 **
 **     Revision    : No.  Name        Date/Time        Content
 ** ###################################################################*/
/*!
 ** @file ProcessorExpert.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
 **  @{
 */
/* MODULE ProcessorExpert */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "SM_SPI1.h"
#include "SS_SPI0.h"
#include "CsIO_UART2.h"
#include "IO2.h"
#include "SysTick.h"
#include "BitIO_NOT_PWDN.h"
#include "BitIO_NOT_RESET.h"
#include "BitIO_START.h"
#include "BitIO_DAISY_IN.h"
#include "BitIO_CLKSEL.h"
#include "EINT_NOT_DRDY.h"
#include "EINT_SYNC_INT.h"
#include "DMAT_M_SPI_TX.h"
#include "DMA_CTRL.h"
#include "DMAT_M_SPI_RX.h"
#include "DMAT_S_SPI_TX.h"
#include "DMAT_S_SPI_RX.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "SPI_PDD.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "MyHeaders.h"

/* 
 * ===================================================================
 * Macros
 * ===================================================================
 */
#define MSG_SIZE 2000

/* 
 * ===================================================================
 * Global Variables
 * ===================================================================
 */
extern TADCDataPtr adcDataPtr;
volatile byte* uploadBufferPtr = NULL;
volatile byte msg[MSG_SIZE] = {0};
volatile byte msg2[MSG_SIZE] = {0};

/* 
 * ===================================================================
 * Main Function
 * ===================================================================
 */
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
    /* Write your local variable definition here */
    extern bool flagSPI1RxDMATransCompleted;
    uint8 len = 20;
    uint8 count = 0;
    byte i = 0;
    byte* rs = NULL;
    byte cmd = 0xFFU;
    byte strCmd[3] = {0};
    byte ans[30] = {0xFFU, 0xFFU, 0xFFU, 0xFFU};
    byte dummy[MSG_SIZE] = {0};
    byte data[100] = {0};
    byte hw[] = "Hello World!";
    
    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init();
    /*** End of Processor Expert internal initialization.                    ***/

    /* Write your code here */
    /* For example: for(;;) { } */
    
    /* Initialize on-chip and peripheral devices */
#if DEBUG
    GPIOTest();
    printf("+UserInit begins...\n");
#endif
    UserInit();
#if DEBUG
    printf("-UserInit finished.\n");
#endif
    
#if DEBUG
    GPIOTest();
#endif
    
    
    cmd = ADC_CMD_SDATAC;
    ADCSendCommand(&cmd);
    
    cmd = ADC_REG_CONFIG1;
    ADCReadRegister(cmd, &ans[0], 1);
    DelaySomeUs(1);
    printf("%x\n", ans[0]);
    
    cmd = ADC_REG_CONFIG1;
    data[0] = 0xAAU;
    ADCWriteRegister(cmd, &data[0], 1);
    DelaySomeUs(10);
    
    while(1)
    {
        ADCReadRegister(cmd, &ans[0], 1);
        while(!flagSPI1RxDMATransCompleted);
        flagSPI1RxDMATransCompleted = FALSE;
//        DelaySomeUs(1);
//        printf("%x | ", ans[2]);
    }
    
    while(1)
    {
        ADCReadRegister(cmd, ans, 1);
        for(i = 0; i < 26; i++)
        {
            printf("%x | ", ans[i]);
        }
        printf("\n");
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

/* END ProcessorExpert */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.2 [05.06]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
