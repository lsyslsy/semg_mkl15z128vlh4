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
 **     mail        : pzdongdong@163.com
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
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "ADC.h"
#include "Aliases.h"
#include "Globals.h"
#include "Init.h"
#include "Macros.h"
#include "Process.h"
#include "Settings.h"
#include "stdio.h"
#include "Test.h"
#include "Utilities.h"

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
volatile bool flagMasterReceived = FALSE;
volatile bool flagMasterSent = FALSE;
volatile bool flagSlaveReceived = FALSE;
volatile bool flagSlaveSent = FALSE;
volatile bool flagUartReceived = FALSE;
volatile bool flagUartSent = FALSE;
volatile bool flagDataReady = FALSE;
volatile bool flagUploadReady = FALSE;
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
    uint8 len = 20;
    uint8 count = 0;
    uint32 i = 0;
    byte cmd = 0xFFU;
    byte strCmd[2] = {0};
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

    ADCStopReadDataContinuous();
    
//    ADCReadRegister(ADC_REG_ID, 1, &cmd, 1);
//    printf("ID: %#x\n", cmd);
//    
//    cmd = 0x03U;
//    ADCWriteRegister(ADC_REG_CONFIG1, 1, &cmd, 1);
//    cmd = 0xFFU;
//    ADCReadRegister(ADC_REG_CONFIG1, 1, &cmd, 1);
//    printf("CONFIG1: %#x\n", cmd);
//    
//    cmd = 0xC0U;
//    ADCWriteRegister(ADC_REG_CONFIG3, 1, &cmd, 1);
//    cmd = 0xFFU;
//    ADCReadRegister(ADC_REG_CONFIG3, 1, &cmd, 1);
//    printf("CONFIG3: %#x\n", cmd);
//    
//    cmd = 0x10U;
//    ADCWriteRegister(ADC_REG_CH1SET, 1, &cmd, 1);
//    len = 0xFFU;
//    ADCReadRegister(ADC_REG_CH1SET, 1, &len, 1);
//    printf("CH1SET: %#x\n", len);
//    
//    ADCWriteRegister(ADC_REG_CH2SET, 1, &cmd, 1);
//    len = 0xFFU;
//    ADCReadRegister(ADC_REG_CH2SET, 1, &len, 1);
//    printf("CH2SET: %#x\n", len);
//    
//    ADCWriteRegister(ADC_REG_CH3SET, 1, &cmd, 1);
//    len = 0xFFU;
//    ADCReadRegister(ADC_REG_CH3SET, 1, &len, 1);
//    printf("CH3SET: %#x\n", len);
//
//    ADCWriteRegister(ADC_REG_CH4SET, 1, &cmd, 1);
//    len = 0xFFU;
//    ADCReadRegister(ADC_REG_CH4SET, 1, &len, 1);
//    printf("CH4SET: %#x\n", len);
//    
//    ADCWriteRegister(ADC_REG_CH5SET, 1, &cmd, 1);
//    len = 0xFFU;
//    ADCReadRegister(ADC_REG_CH5SET, 1, &len, 1);
//    printf("CH5SET: %#x\n", len);
//    
//    ADCWriteRegister(ADC_REG_CH6SET, 1, &cmd, 1);
//    len = 0xFFU;
//    ADCReadRegister(ADC_REG_CH6SET, 1, &len, 1);
//    printf("CH6SET: %#x\n", len);
//    
//    ADCWriteRegister(ADC_REG_CH7SET, 1, &cmd, 1);
//    len = 0xFFU;
//    ADCReadRegister(ADC_REG_CH7SET, 1, &len, 1);
//    printf("CH7SET: %#x\n", len);
//    
//    ADCWriteRegister(ADC_REG_CH8SET, 1, &cmd, 1);
//    len = 0xFFU;
//    ADCReadRegister(ADC_REG_CH8SET, 1, &len, 1);
//    printf("CH8SET: %#x\n", len);
//
//    cmd = 0xF0U;
//    ADCWriteRegister(ADC_REG_GPIO, 1, &cmd, 1);
//    cmd = 0xFFU;
//    ADCReadRegister(ADC_REG_GPIO, 1, &cmd, 1);
//    printf("GPIO: %#x\n", cmd);
//    
//    ADCReadDataContinuous();
//    ADCStartConvertByCommand();
    
//    while(1)
//    {
////        ADCReadRegister(ADC_REG_ID, 1, &cmd, 1);
////        printf("%#x\n", cmd);
//        while(!flagDataReady);
//        flagDataReady = FALSE;
//        ADCReadContinuousData(adcDataPtr->rawData, RAW_DATA_SIZE);
////        ADCReadData(adcDataPtr->rawData, RAW_DATA_SIZE);
//        SplitRawData(adcDataPtr);
////        ADCReadData(msg, MSG_SIZE);
////        printf("Head: %#x\nLOFF_STATP: %#x\nLOFF_STATN: %#x\n", adcDataPtr->head, adcDataPtr->loffStatP, adcDataPtr->loffStatN);
//        for(i = 0; i < USING_CHANNEL_NUMBER; i++)
//        {
//            printf("%#x,", adcDataPtr->channelData[i]);
//        }
////        for(i = 0; i < RAW_DATA_SIZE; i++)
////        {
////            printf("%#x,", adcDataPtr->rawData[i]);
////        }
//        printf("\n");
//        DelaySomeMs(10);
//    }

    for(i = 0; i < MSG_SIZE; i++)
    {
        msg[i] = i;
        msg[i] = 1999 - i;
    }
    
    cmd = 0xFF;
    while(cmd != 0xA1)
    {
//        SPI1Send(dummy, MSG_SIZE);
//        SPI1Receive(msg, MSG_SIZE);
//        SPI1EnableInterrupt();
//        while(!flagMasterReceived);
//        flagMasterReceived = TRUE;
        
        SPI0Receive(&cmd, 1);
        SPI0EnableRxInterrupt();
        while(!flagSlaveReceived);
        flagSlaveReceived = FALSE;
//        printf("%#x\n", cmd);
    }
    
    cmd = 0xA2;
    SPI0Send(&cmd, 1);
    SPI0EnableTxInterrupt();
    while(!flagSlaveSent);
    flagSlaveSent = FALSE;
//    DelayMs(10);
            
    while(1)
    {
        EIntSyncInterruptEnable(EINT_SYNC_INT);
        while(!flagUploadReady);
        SPI0Send(uploadBufferPtr, MSG_SIZE);
        SPI0EnableRxInterrupt();
        while(!flagSlaveSent);
        flagUploadReady = FALSE;
        flagSlaveSent = FALSE;
        
    }
        
//  for(i = 0; i < 100; i++)
//  {
//    printf("%#x,", msg[i]);
//  }
//  printf("\n");
//  DelayMs(1);
        
    while(1);
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
