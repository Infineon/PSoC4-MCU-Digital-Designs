/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  This project demonstrates operation of the PrISM component.
*  When the code is run, LEDs are blinking.
*  PrISM configuration:
*   Resolution: 8-bit
*   PulseType0: Less Than or Equal
*   PulseType1: Greater Than or Equal
*  
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <device.h>

#define FORWARD   (1u)

uint8 density;
uint8 direction;


/*******************************************************************************
* Function Name: Sleep_Start
********************************************************************************
*
* Summary:
*   Local Interrupt Service Routine for changing LED contrast.
*******************************************************************************/
CY_ISR(Timer)
{
    /* flip direction at max and min points */
    if((density == 0u) ||(density == 0xffu))
    {
        direction ^= FORWARD;
    }
    /* change density for the LEDs*/
    if(direction & FORWARD)
    {
        density++;
    }
    else
    {
        density--;
    }
    /* overwrite density to PrISM registers */
    PrISM_1_WritePulse0(density);
    PrISM_1_WritePulse1(density);
}


void main()
{
    /* Init ISR connected to the TC pin for change LED contrast */
    isr_Timer_StartEx(Timer);
    
    /* Start PrISM */
    PrISM_1_Start();

    /* Enable Global Interrupts */
    CyGlobalIntEnable;
    
    /* No work has to be done in main loop */
    while(1u);
    
}


/* [] END OF FILE */
