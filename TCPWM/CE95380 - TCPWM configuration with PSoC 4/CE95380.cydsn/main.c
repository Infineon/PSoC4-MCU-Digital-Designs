/*******************************************************************************
* File Name: main.c
*
* Version: 2.00
*
* Description:
*  This is source code for the datasheet example of the TCPWM (Unconfigured 
*  mode) component.
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>

uint32 InterruptHpn;


/*******************************************************************************
* Define Interrupt service routine and allocate an vector to the Interrupt
********************************************************************************/
CY_ISR(InterruptHandler)
{
    /* Check interrupt source and clear Inerrupt */
    InterruptHpn = TCPWM_GetInterruptSourceMasked();
   	if (InterruptHpn == TCPWM_INTR_MASK_CC_MATCH)
    {
        TCPWM_ClearInterrupt(TCPWM_INTR_MASK_CC_MATCH);
        LED_GREEN_Write(0u);
        CyDelay(200u);
        LED_GREEN_Write(1u);
    }
    else
    {
        TCPWM_ClearInterrupt(TCPWM_INTR_MASK_TC);
        LED_BLUE_Write(0u);
        CyDelay(200u);
        LED_BLUE_Write(1u);
    }
}

void main()
{   
    #if !(CY_PSOC4A)
        CySysWdtDisable();
    #endif /* !(CY_PSOC4A) */
       
    CyDelay(50);
    
    /* Enable the global interrupt */
    CyGlobalIntEnable;
    
    /* Enable the Interrupt component connected to interrupt */
    TC_CC_ISR_StartEx(InterruptHandler);

	/* Start the components */
    TCPWM_Start();

    /* Set Compare Mode */
    TCPWM_SetMode(TCPWM_MODE_TIMER_COMPARE);
    
    /* TCPWM Period & Compare */   	
    TCPWM_WritePeriod(65535u);
    TCPWM_WriteCompare(20000u);
    
	/* Set UP Mode */
	TCPWM_SetCounterMode(TCPWM_COUNT_UP);
    
	/* Set Prescaler 1x */
	TCPWM_SetPrescaler(TCPWM_PRESCALE_DIVBY1);
    
	/* Set interrupt mode (TC/CC)*/
	TCPWM_SetInterruptMode(TCPWM_INTR_MASK_CC_MATCH | TCPWM_INTR_MASK_TC);
    
    /* Set start trigger */
    TCPWM_TriggerCommand(TCPWM_MASK, TCPWM_CMD_START);
    
    for(;;)
    {
    }
}

/* [] END OF FILE */

