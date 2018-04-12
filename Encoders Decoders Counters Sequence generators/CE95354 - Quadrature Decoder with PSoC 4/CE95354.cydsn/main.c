/*******************************************************************************
* File Name: main.c
*
* Version: 2.00
*
* Description:
*  This is source code for the datasheet example of the TCPWM (Quadrature 
*  Decoder mode) component.
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

#define DELAY       (0x0u)
#define UP          (0x1u)
#define DOWN        (0x0u)
#define CNT_PULSE   (0x8000u)

uint32 InterruptCnt;


/*******************************************************************************
* Define Interrupt service routine and allocate an vector to the Interrupt
********************************************************************************/
CY_ISR(InterruptHandler)
{
	/* Clear Inerrupt */
   	QuadDec_ClearInterrupt(QuadDec_INTR_MASK_CC_MATCH);
    
    LED_GREEN_Write(0u);
    CyDelay(200u);
    LED_GREEN_Write(1u);  
}


/*******************************************************************************
* Function Name: PhiAbGeneration
********************************************************************************
*
* Summary:
*  Generates PhiA pulses
*
* Parameters direction: 
*  count: count of pulses
*
* Return:
*  None
*
*******************************************************************************/
static void PhiAbGeneration(uint32 count)
{
	uint32 tmp;
	
	for(tmp=0; tmp < count; tmp++)
	{
            phiA_Out_Write (UP); 
			CyDelay(DELAY);
			phiA_Out_Write (DOWN); 
            CyDelay(DELAY);
	}
}


void main()
{
    #if !(CY_PSOC4A)
        CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK);
    #endif /* !(CY_PSOC4A) */
     
    CyDelay(50u);
    
    /* Enable the global interrupt */
    CyGlobalIntEnable;
    
    /* Enable the Interrupt component connected to interrupt */
    CC_ISR_StartEx(InterruptHandler);

	/* Start the components */
    QuadDec_Start();

    /* Set index trigger */
    QuadDec_TriggerCommand(QuadDec_MASK, QuadDec_CMD_RELOAD);
    
    for(;;)
    {
        PhiAbGeneration(CNT_PULSE);
    }
}

/* [] END OF FILE */
