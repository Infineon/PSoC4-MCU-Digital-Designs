/*******************************************************************************
* File: main.c
*
* Version: 1.10 
*
*  Description:
*    This is a source code for example project of LUT
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
uint8 output;
uint8 i;
uint8 err;


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
* Main function performs following functions:
*  1. Initializes the LCD and clears the display
*  2. Sets the input using control register
*  3. Stores the output in status register
*
*  Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void main()
{
    err = 0u;

    /* Start the clock and the LCD */
    status_clock_Enable();
    CharLCD_Start();
    CharLCD_ClearDisplay();
    
    /* Test each of the LUT input combinations */
    for(i = 0u; i < 4u; i++ )
    {
        Control_Reg_Write(i);
        output = Status_Reg_Read();

        /* If input != output something is wrong with the LUT */
        if ( i != output)
        {
            err++;
        }
        
        /* Display the output on LCD */
        CyDelay(1000u);
        CharLCD_Position(0u, 0u);
        CharLCD_PrintInt8(i);
        CharLCD_Position(1u, 0u);
        CharLCD_PrintInt8(output);
    }
    
    CharLCD_Position(0u, 0u);
    CharLCD_PrintString("Test");
    CharLCD_Position(1u, 0u);
    
    /* Display the end result on LCD */
    if(err != 0u)
    {
        CharLCD_PrintString("Failed");
    } else {
        CharLCD_PrintString("Passed");
    }
    
    for(;;)
    {
    }
}


/* [] END OF FILE */
