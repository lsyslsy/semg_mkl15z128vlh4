/* ###################################################################
 **     Filename    : Events.c
 **     Project     : ProcessorExpert
 **     Processor   : MKL15Z128VLH4
 **     Component   : Events
 **     Version     : Driver 01.00
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2013-07-11, 23:27, # CodeGen: 0
 **     Abstract    :
 **         This is user's event module.
 **         Put your event handler code here.
 **     Settings    :
 **     Contents    :
 **         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
 **
 ** ###################################################################*/
/*!
 ** @file Events.c
 ** @version 01.00
 ** @brief
 **         This is user's event module.
 **         Put your event handler code here.
 */
/*!
 **  @addtogroup Events_module Events module documentation
 **  @{
 */
/* MODULE Events */

#include "Aliases.h"
#include "Cpu.h"
#include "Events.h"
#include "Globals.h"
#include "SysTick_PDD.h"
#include "SysTick.h"
#include "Utilities.h"

#ifdef __cplusplus
extern "C"
{   
#endif 

/* User includes (#include below this line is not maintained by Processor Expert) */

/* 
 * ===================================================================
 * Global Variables
 * ===================================================================
 */
extern volatile bool flagMasterReceived;
extern volatile bool flagMasterSent;
extern volatile bool flagSlaveReceived;
extern volatile bool flagSlaveSent;
extern volatile bool flagDataReady;
extern volatile bool flagUartReceived;
extern volatile bool flagUartSent;
extern volatile bool flagUploadReady;
extern volatile bool flagDelayed;
extern volatile byte* uploadBufferPtr;

/*
 ** ===================================================================
 **     Event       :  Cpu_OnNMIINT (module Events)
 **
 **     Component   :  Cpu [MKL15Z128LK4]
 **     Description :
 **         This event is called when the Non maskable interrupt had
 **         occurred. This event is automatically enabled when the <NMI
 **         interrupt> property is set to 'Enabled'.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void Cpu_OnNMIINT(void)
{
    /* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  SS_SPI0_OnBlockSent (module Events)
 **
 **     Component   :  SS_SPI0 [SPISlave_LDD]
 */
/*!
 **     @brief
 **         This event is called after the last character from the
 **         output buffer is moved to the transmitter. This event is
 **         available only if the SendBlock method is enabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. The pointer is passed
 **                           as the parameter of Init method. 
 */
/* ===================================================================*/
void SS_SPI0_OnBlockSent(LDD_TUserData *UserDataPtr)
{
    /* Write your code here ... */
    flagSlaveSent = TRUE;
}

/*
 ** ===================================================================
 **     Event       :  SS_SPI0_OnBlockReceived (module Events)
 **
 **     Component   :  SS_SPI0 [SPISlave_LDD]
 */
/*!
 **     @brief
 **         This event is called when the requested number of data is
 **         moved to the input buffer. This method is available only if
 **         the ReceiveBlock method is enabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. The pointer is passed
 **                           as the parameter of Init method. 
 */
/* ===================================================================*/
void SS_SPI0_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
    /* Write your code here ... */
    flagSlaveReceived = TRUE;
}

/*
 ** ===================================================================
 **     Event       :  SM_SPI1_OnBlockSent (module Events)
 **
 **     Component   :  SM_SPI1 [SPIMaster_LDD]
 */
/*!
 **     @brief
 **         This event is called after the last character from the
 **         output buffer is moved to the transmitter. This event is
 **         available only if the SendBlock method is enabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. The pointer is passed
 **                           as the parameter of Init method. 
 */
/* ===================================================================*/
void SM_SPI1_OnBlockSent(LDD_TUserData *UserDataPtr)
{
    /* Write your code here ... */
    flagMasterSent = TRUE;
}

/*
 ** ===================================================================
 **     Event       :  SM_SPI1_OnBlockReceived (module Events)
 **
 **     Component   :  SM_SPI1 [SPIMaster_LDD]
 */
/*!
 **     @brief
 **         This event is called when the requested number of data is
 **         moved to the input buffer. This method is available only if
 **         the ReceiveBlock method is enabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. The pointer is passed
 **                           as the parameter of Init method. 
 */
/* ===================================================================*/
void SM_SPI1_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
    /* Write your code here ... */
    flagMasterReceived = TRUE;
}

/*
 ** ===================================================================
 **     Event       :  AS_UART2_OnBlockReceived (module Events)
 **
 **     Component   :  AS_UART2 [Serial_LDD]
 */
/*!
 **     @brief
 **         This event is called when the requested number of data is
 **         moved to the input buffer.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void AS_UART2_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
    /* Write your code here ... */
    flagUartReceived = TRUE;
}

/*
 ** ===================================================================
 **     Event       :  AS_UART2_OnBlockSent (module Events)
 **
 **     Component   :  AS_UART2 [Serial_LDD]
 */
/*!
 **     @brief
 **         This event is called after the last character from the
 **         output buffer is moved to the transmitter. 
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void AS_UART2_OnBlockSent(LDD_TUserData *UserDataPtr)
{
    /* Write your code here ... */
    flagUartSent = TRUE;
}

/*
 ** ===================================================================
 **     Event       :  EINT_NOT_DRDY_OnInterrupt (module Events)
 **
 **     Component   :  EINT_NOT_DRDY [ExtInt_LDD]
 */
/*!
 **     @brief
 **         This event is called when an active signal edge/level has
 **         occurred.
 **     @param
 **         UserDataPtr     - Pointer to RTOS device
 **                           data structure pointer.
 */
/* ===================================================================*/
void EINT_NOT_DRDY_OnInterrupt(LDD_TUserData *UserDataPtr)
{
    /* Write your code here ... */

    
    flagDataReady = TRUE;
}

/*
 ** ===================================================================
 **     Event       :  EINT_SYNC_INT_OnInterrupt (module Events)
 **
 **     Component   :  EINT_SYNC_INT [ExtInt_LDD]
 */
/*!
 **     @brief
 **         This event is called when an active signal edge/level has
 **         occurred.
 **     @param
 **         UserDataPtr     - Pointer to RTOS device
 **                           data structure pointer.
 */
/* ===================================================================*/
void EINT_SYNC_INT_OnInterrupt(LDD_TUserData *UserDataPtr)
{
    /* Write your code here ... */
    extern volatile byte msg[2000];
    extern volatile byte msg2[2000];
    
    EIntSyncInterruptDisable(EINT_SYNC_INT);
    
    uploadBufferPtr = (uploadBufferPtr == msg) ? msg2 : msg;
    
    flagUploadReady = TRUE;
}

/*
 * ===================================================================
 *     Method      : SysTick_OnInterrupt(module Events)
 */
/*!
 *     @brief
 *          This event is called when a SysTick countdown has been 0.  	
 */
/* ===================================================================*/
void SysTick_OnInterrupt(void)
{
    
}

/*
 ** ===================================================================
 **     Method      :  SysTick_Interrupt (component SysTick)
 **
 **     Description :
 **         The ISR function handling the device SysTick interrupt.
 **         This method is internal. It is used by Processor Expert only.
 ** ===================================================================
 */
PE_ISR(SysTick_Interrupt)
{
    flagDelayed = TRUE;
    SysTickDisable();
    SysTickClearCountFlag();
}

/* END Events */

#ifdef __cplusplus
} /* extern "C" */
#endif 

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
