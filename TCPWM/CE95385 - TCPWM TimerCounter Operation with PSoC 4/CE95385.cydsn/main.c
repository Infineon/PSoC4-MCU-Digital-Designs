/*******************************************************************************
* File Name: main.c
*
* Version: 2.00
*
* Description:
*  This is source code for the datasheet example of the TCPWM (Timer / Counter 
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
    InterruptHpn = Timer_GetInterruptSourceMasked();
   	if (InterruptHpn == Timer_INTR_MASK_CC_MATCH)
    {
        Timer_ClearInterrupt(Timer_INTR_MASK_CC_MATCH);
        LED_GREEN_Write(0u);
        CyDelay(200);
        LED_GREEN_Write(1u);
    }
    else
    {
        Timer_ClearInterrupt(Timer_INTR_MASK_TC);
        LED_BLUE_Write(0u);
        CyDelay(200);
        LED_BLUE_Write(1u);
    }
}

void main()
{   
    #if !(CY_PSOC4A)
        CySysWdtDisable();
    #endif /* !(CY_PSOC4A) */
       
    CyDelay(50u);
    
    /* Enable the global interrupt */
    CyGlobalIntEnable;
    
    /* Enable the Interrupt component connected to interrupt */
    TC_CC_ISR_StartEx(InterruptHandler);

	/* Start the components */
    Timer_Start();

    for(;;)
    {
        /* Capture signal generation */
        Capture_Out_Write(1u);
        CyDelayUs(50u);
        Capture_Out_Write(0u);
        
        /* Capture signal will be generated for each 5s */
        CyDelay(5000u);
    }
}

/* [] END OF FILE */
