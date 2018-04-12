/*******************************************************************************
* File Name: main.c
*
* Version: 2.00
*
* Description:
*  This is source code for the datasheet example of the TCPWM (PWM 
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

#define BRIGHTNESS_DECREASE         (100u)

uint16 curPos;


/*******************************************************************************
* Define Interrupt service routine and allocate an vector to the Interrupt
********************************************************************************/
CY_ISR(InterruptHandler)
{
	/* Clear TC Inerrupt */
   	PWM_ClearInterrupt(PWM_INTR_MASK_TC);
    
	/* Increment the Compare for LED brighrness decrease */ 
    PWM_WriteCompare(PWM_ReadCompare() + BRIGHTNESS_DECREASE);
}

int main()
{
    #if !(CY_PSOC4A)
        CySysWdtDisable();
    #endif /* !(CY_PSOC4A) */
    
    CyDelay(50u);
    
    /* Enable the global interrupt */
    CyGlobalIntEnable;
 
    /* Enable the Interrupt component connected to interrupt */
    TC_ISR_StartEx(InterruptHandler);
    
	/* Start the components */
    PWM_Start();
    PWM_WritePeriod(65300u);
    
    for(;;)
    {
        
    }
}


/* [] END OF FILE */
