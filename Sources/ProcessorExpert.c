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
#include "BitIO_UPRDY.h"
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
    byte cmd;
    byte reg;
    byte regVal[25];
    byte dummy[MSG_SIZE];
    bool flag1 = TRUE;
    uint16 i;
    extern volatile bool flagSPI1RxDMATransCompleted;
    extern volatile bool flagSPI0TxDMATransCompleted;
    extern volatile bool flagDataReady;
    extern volatile bool flagUploadReady;
    extern TADCDataPtr adcDataPtr;
    
    
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
    
    for(i = 0; i < MSG_SIZE; i++)
    {
        msg[i] = 0xAAU;
        msg2[i] = 0xBBU;
    }
    msg[MSG_SIZE - 1] = 0x01U;
    msg2[MSG_SIZE - 1] = 0x20U;
    
    cmd = ADC_CMD_SDATAC;
    ADCSendCommand(&cmd);
    
    regVal[0] = 0x60U;
    ADCWriteRegister(ADC_REG_CONFIG3, regVal, 1);
    ADCReadRegister(ADC_REG_CONFIG3, regVal, 1);
    printf("CONFIG3: %#x\n", regVal[0]);

    regVal[0] = 0x10U;
    regVal[1] = 0x10U;
    regVal[2] = 0x10U;
    regVal[3] = 0x10U;
    regVal[4] = 0x10U;
    regVal[5] = 0x10U;
    regVal[6] = 0x10U;
    regVal[7] = 0x10U;
    ADCWriteRegister(ADC_REG_CH1SET, regVal, 8);
    for(i = 0; i < 8; i++)
    {
        regVal[i] = 0x00U;
    }
    for(;;)
    ADCReadRegister(ADC_REG_CH1SET, regVal, 8);
    printf("%#x, %#x, %#x, %#x, %#x, %#x, %#x, %#x\n", regVal[0], regVal[1], regVal[2], regVal[3], regVal[4], regVal[5], regVal[6], regVal[7]);

    
    cmd = ADC_CMD_RDATAC;
    ADCSendCommand(&cmd);
    
    EIntNotReadyEnable(EINT_NOT_DRDY);
    EIntSyncInterruptEnable(EINT_SYNC_INT);
    
    cmd = ADC_CMD_START;
    ADCSendCommand(&cmd);
    
    for(;;)
    {
        /* If data of ADC is ready, read it. */
        if(flagDataReady)
        {
            if(!flagSPI1RxDMATransCompleted && !adcDataPtr->flagReceivingData)
            {
                ADCReadContinuousData(adcDataPtr->rawData, RAW_DATA_SIZE);
                adcDataPtr->flagReceivingData = TRUE;
            }
            if(flagSPI1RxDMATransCompleted)
            {
                flagSPI1RxDMATransCompleted = FALSE;
                adcDataPtr->flagReceivingData = FALSE;
                SplitRawData(adcDataPtr);
                printf("%#x %#x %#x %#x | %#x %#x %#x %#x %#x %#x %#x %#x\n", adcDataPtr->head, adcDataPtr->loffStatP,
                                                                                adcDataPtr->loffStatN, adcDataPtr->regGPIOData,
                                                                                adcDataPtr->channelData[0], adcDataPtr->channelData[1],
                                                                                adcDataPtr->channelData[2], adcDataPtr->channelData[3],
                                                                                adcDataPtr->channelData[4], adcDataPtr->channelData[5],
                                                                                adcDataPtr->channelData[6], adcDataPtr->channelData[7]);
                flagDataReady = FALSE;
            }
        }
        
        
        /*  If the ARM requires data, transmit. */
        if(flagUploadReady && flagSPI0TxDMATransCompleted)
        {
            flagUploadReady = FALSE;
            flagSPI0TxDMATransCompleted = FALSE;
            IOUploadReadyClrVal();
            if(flag1)
            {
                SPI0ReceiveSendData((LDD_DMA_TAddress)msg, (LDD_DMA_TAddress)dummy,
                                    (LDD_DMA_TByteCount)MSG_SIZE, (LDD_DMA_TByteCount)MSG_SIZE);
                flag1 = FALSE;
            }
            else
            {
                SPI0ReceiveSendData((LDD_DMA_TAddress)msg2, (LDD_DMA_TAddress)dummy,
                                    (LDD_DMA_TByteCount)MSG_SIZE, (LDD_DMA_TByteCount)MSG_SIZE);
                flag1 = TRUE;
            }
        }
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
