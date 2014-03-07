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
#include "WaitTimer.h"
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
//const int MSG_SIZE = 2000;

/*
 * ===================================================================
 * Global Variables
 * ===================================================================
 */
//volatile byte* uploadBufferPtr = NULL;
//volatile byte msg[MSG_SIZE] = {0};
//volatile byte msg2[MSG_SIZE] = {0};

/*
 * ===================================================================
 * For Communication
 * ===================================================================
 */

//For shake hand
volatile byte rxbuf_shakehand[SHAKEHAND_SIZE] =
{ 0 };
volatile byte txbuf_shakehand[SHAKEHAND_SIZE] =
{ 0 };
volatile bool SPINeedWait = FALSE ;

static void SPIWaitIdle(uint16_t ms )
{
	SPINeedWait = TRUE;
	WaitTimer_Disable(NULL);
	WaitTimer_SetPeriodTicks(NULL,24*1000*ms);
	//WaitTimer_ResetCounter(NULL);
	WaitTimer_Enable(NULL);
}
static void MoveADCDataToMCUData()
{
	static uint8 ch_dat_cnt = 0;
	uint8 ch_num;
	for ( ch_num = 0; ch_num < 8; ch_num++)
	{
		tMCUPtr->mcuData.channelData[ch_num][ch_dat_cnt] =
				tADCPtr[0]->adcData.channelData[ch_num];
	}
	++ch_dat_cnt;
	ch_dat_cnt %= CHANNEL_DATA_COUNT;

}
/*
 * ===================================================================
 * Main Function
 * ===================================================================
 */
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
/*!
 *     @brief
 *          The main function of the project.
 *     @param
 *          void
 *     @return
 *          int
 */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
    /* Write your local variable definition here */
    extern TADCPtr tADCPtr[USING_ADC_COUNT];
    extern TMCUPtr tMCUPtr;
    extern TARMPtr tARMPtr;
    byte cmd;
    //byte reg;
    byte regVal[25] = {0};
    byte regVal2[25] = {0};
    byte dummy[MSG_SIZE];
    unsigned char stage = 1;
    bool flag1 = TRUE;//缓存切换标识
    uint16 i;

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

//    for(i = 0; i < MSG_SIZE; i++)
//    {
//        msg[i] = 0xAAU;
//        msg2[i] = 0xBBU;
//    }
//    PrepareTheMSG();
//    msg[MSG_SIZE - 1] = 0xCCU;
//    msg2[MSG_SIZE - 1] = 0xDDU;

    cmd = ADC_CMD_SDATAC;
    ADCSendCommand(&cmd);
    while(!tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted || !tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted);
    tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted = FALSE;
    tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted = FALSE;

    cmd = ADC_REG_ID;
    ADCReadRegister(cmd, regVal, 1);
    while(!tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted || !tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted);
    tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted = FALSE;
    tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted = FALSE;
    printf("ID: %#x\n", regVal[2]);
    for(i = 0; i < 10; i++)
    {
        regVal[i] = 0xFF;
    }

    cmd = ADC_REG_CONFIG3;
    regVal2[0] = 0x60U;
    ADCWriteRegister(cmd, regVal2, 1);
    while(!tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted && !tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted);
    tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted = FALSE;
    tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted = FALSE;
    for(i = 0; i < 10; i++)
    {
        regVal2[i] = 0xFF;
    }
    
//    DelaySomeMs(100);
    ADCReadRegister(cmd, regVal2, 1);
    while(!tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted && !tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted);
    tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted = FALSE;
    tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted = FALSE;
    DelaySomeMs(1);
    printf("CONFIG3: %#x\n", regVal2[2]);
    for(i = 0; i < 10; i++)
    {
        regVal2[i] = 0xFF;
    }

//
//    regVal[0] = 0x10U;
//    regVal[1] = 0x10U;
//    regVal[2] = 0x10U;
//    regVal[3] = 0x10U;
//    regVal[4] = 0x10U;
//    regVal[5] = 0x10U;
//    regVal[6] = 0x10U;
//    regVal[7] = 0x10U;
//    ADCWriteRegister(ADC_REG_CH1SET, regVal, 8);
//    for(i = 0; i < 8; i++)
//    {
//        regVal[i] = 0x00U;
//    }
//    ADCReadRegister(ADC_REG_CH1SET, regVal, 8);
//    printf("%#x, %#x, %#x, %#x, %#x, %#x, %#x, %#x\n", regVal[0], regVal[1], regVal[2], regVal[3], regVal[4], regVal[5], regVal[6], regVal[7]);


    cmd = ADC_CMD_RDATAC;
    ADCSendCommand(&cmd);
    while(!tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted || !tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted);
    tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted = FALSE;
    tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted = FALSE;

    EIntNotReadyEnable(EINT_NOT_DRDY);
    EIntSyncInterruptEnable(EINT_SYNC_INT);

    cmd = ADC_CMD_START;
    ADCSendCommand(&cmd);
    while(!tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted || !tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted);
    tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted = FALSE;
//    tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted = FALSE;
    tMCUPtr->mcuStatus.isSPI0TxDMATransCompleted = TRUE; //First time needs
    for(;;)
    {
        /* If data of ADC is ready, read it. */
        if(tADCPtr[0]->adcStatus.isDataReady)
        {
            if(!tMCUPtr->mcuStatus.isReceivingADCData && tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted)
            {
                ADCReadContinuousData(tADCPtr[0]->adcData.rawData, RAW_DATA_SIZE);
                tMCUPtr->mcuStatus.isReceivingADCData = TRUE;
                tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted = FALSE;
            }
            if(tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted)
            {
                tMCUPtr->mcuStatus.isReceivingADCData = FALSE;
                SplitRawData(&(tADCPtr[0]->adcData));
//                printf("%#x %#x %#x %#x | %#x %#x %#x %#x %#x %#x %#x %#x\n", tADCPtr[0]->adcData.head, tADCPtr[0]->adcData.loffStatP,
//                                                                                tADCPtr[0]->adcData.loffStatN, tADCPtr[0]->adcData.regGPIOData,
//                                                                                tADCPtr[0]->adcData.channelData[0], tADCPtr[0]->adcData.channelData[1],
//                                                                                tADCPtr[0]->adcData.channelData[2], tADCPtr[0]->adcData.channelData[3],
//                                                                                tADCPtr[0]->adcData.channelData[4], tADCPtr[0]->adcData.channelData[5],
//                                                                                tADCPtr[0]->adcData.channelData[6], tADCPtr[0]->adcData.channelData[7]);
                printf("AD\n");
                tADCPtr[0]->adcData.head = 0xFFU;
//                tADCPtr[0]->adcData.loffStatP = 0xFFU;
//                tADCPtr[0]->adcData.loffStatN = 0xFFU;
//                tADCPtr[0]->adcData.regGPIOData = 0xFFU;
//                memset(tADCPtr[0]->adcData.rawData, 0xFFU, sizeof(tADCPtr[0]->adcData.rawData));
//                memset(tADCPtr[0]->adcData.channelData, 0xFF, sizeof(tADCPtr[0]->adcData.channelData));
               MoveADCDataToMCUData();
                tADCPtr[0]->adcStatus.isDataReady = FALSE;
                

            }
        }
        
        //MoniData();
        /*  If the ARM requires data, transmit. */
       // SPINeedWait = TRUE;
        if(!SPINeedWait)
        if(tARMPtr->armStatus.isRequiringData && tMCUPtr->mcuStatus.isSPI0TxDMATransCompleted)
        {
            tARMPtr->armStatus.isRequiringData = FALSE;
            tMCUPtr->mcuStatus.isSPI0TxDMATransCompleted = FALSE;
			if (flag1)
			{
				DataFrame_Prepare((byte*) tARM.armDataLeft.dataFrame);
			}
			else
			{
				DataFrame_Prepare((byte*) tARM.armDataRight.dataFrame);
			}
			if (stage == 1) //开始握手
			{

				rxbuf_shakehand[0] = 0xFF;
				rxbuf_shakehand[1] = 0xFF;
				rxbuf_shakehand[2] = 0xFF;
				//MOSI 收3个字节
                //开启DMA之前需要清空接收缓冲区标志
				//不能加tmp = SPI_D SPI_S  影响DMA状态
				SPI0ReceiveSendData((LDD_DMA_TAddress) txbuf_shakehand,
						(LDD_DMA_TAddress) rxbuf_shakehand,
						(LDD_DMA_TByteCount) 4, (LDD_DMA_TByteCount) 4);
				IOUploadReadyClrVal();
				//PTE20_PutVal(NULL, TRUE);
				while (! tMCUPtr->mcuStatus.isSPI0TxDMATransCompleted)
					; //必须要等  不然切到上面不知道多久哦了
			//	PTE20_PutVal(NULL, FALSE);
				if(rxbuf_shakehand[0] == 0 && rxbuf_shakehand[1] == 0xa5)
				{
					rxbuf_shakehand[0] = rxbuf_shakehand[1];
					rxbuf_shakehand[1] = rxbuf_shakehand[2];
					rxbuf_shakehand[2] = rxbuf_shakehand[3];
				//	rxbuf_shakehand[0] = rxbuf_shakehand[1];
					
				}
				if (rxbuf_shakehand[0]
						!= 0xa5 || rxbuf_shakehand[1] != BRANCH_NUM)
					{
					//做10ms 时隙退避
					//DelayMs(10);//错了 必须要等 以后可用定时器实现 以便占用读取AD，时间
					SPIWaitIdle(10);
					printf("wait for 10ms");
				//	SCB_AIRCR |= SCB_AIRCR_VECTKEY(0x5fa);
				//	SCB_AIRCR |= SCB_AIRCR_SYSRESETREQ_MASK;
					goto sh_failed;
					}
				stage = 2;
			}

			if (stage == 2)
			{
				stage = 1;
				switch (rxbuf_shakehand[2])
				{
				case CMD_SHKEHAND:
					 tMCUPtr->mcuStatus.isSPI0TxDMATransCompleted = FALSE;
					//MISO 发3个字节  由于错误SPICLK时钟  3+1=4
					txbuf_shakehand[0] = 0xb6; //182
					txbuf_shakehand[1] = BRANCH_NUM;
					txbuf_shakehand[2] = STATE_OK; //1
					SPI0ReceiveSendData((LDD_DMA_TAddress) txbuf_shakehand,
							(LDD_DMA_TAddress) rxbuf_shakehand,
							(LDD_DMA_TByteCount) 4, (LDD_DMA_TByteCount) 4);
					//while (!flagSPI0TxDMATransCompleted)
					//	;
					break;
				case CMD_TRANSFER:
					tMCUPtr->mcuStatus.isSPI0TxDMATransCompleted = FALSE;
					//DMACheckNeeded = TRUE;
					//发送AD数据包
					if (flag1)
					{
						SPI0ReceiveSendData((LDD_DMA_TAddress) tARM.armDataLeft.dataFrame,
								(LDD_DMA_TAddress) dummy,
								(LDD_DMA_TByteCount) MSG_SIZE + 1,
								(LDD_DMA_TByteCount) MSG_SIZE) + 1;
						//flag1 = FALSE;
					}
					else
					{
						SPI0ReceiveSendData((LDD_DMA_TAddress) tARM.armDataRight.dataFrame,
								(LDD_DMA_TAddress) dummy,
								(LDD_DMA_TByteCount) MSG_SIZE + 1,
								(LDD_DMA_TByteCount) MSG_SIZE) + 1;
						//flag1 = TRUE;
					}
					break;
				default:
					break;
				}
			}
			sh_failed: ;
        }
			
    } //end for

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
