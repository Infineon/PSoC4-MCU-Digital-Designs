/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  This example project demonstrates the basic operation of the EZI2C slave
*  (SCB mode) component. The EZI2C slave accepts a packet with a command from
*  the I2C master to control the RGB LED color. The EZI2C slave updates its
*  buffer with the status packet in response to the accepted command.
*  For more information refer to example project datasheet.
*
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>
#include <header.h>

/* EZI2C slave buffer for write and read */
uint8 ezI2cBuffer[BUFFER_SIZE] = {PACKET_SOP, STS_CMD_FAIL, PACKET_EOP, PACKET_SOP, STS_CMD_FAIL, PACKET_EOP};


/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  The main function performs the following actions:
*   1. Turns off RGB LED.
*   2. Sets up EZI2C slave buffer.
*   3. Starts I2C slave (SCB mode) component.
*   4. Enables global interrupts.
*   5. Waits for command from the I2C master to control the RGB LED.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void main()
{
    uint8 status = STS_CMD_FAIL;

    RGB_LED_OFF;

    /* Setup buffer and start EZI2C slave (SCB mode) */
    EZI2C_EzI2CSetBuffer1(BUFFER_SIZE, READ_ONLY_OFFSET, ezI2cBuffer);
    EZI2C_Start();

    CyGlobalIntEnable;

    for(;;)
    {
        /* Write complete: parse packet */
        if (0u != (EZI2C_EzI2CGetActivity() & EZI2C_EZI2C_STATUS_WRITE1))
        {
            /* Check start and end of packet markers */
            if ((ezI2cBuffer[PACKET_SOP_POS] == PACKET_SOP) &&
                (ezI2cBuffer[PACKET_EOP_POS] == PACKET_EOP))
            {
                status = ExecuteCommand(ezI2cBuffer[PACKET_CMD_POS]);
            }

            /* Update buffer with status */
            ezI2cBuffer[PACKET_STS_POS] = status;
            status = STS_CMD_FAIL;
        }

        /* Buffer is always available to be read */
    }
}


/*******************************************************************************
* ExecuteCommand(): executes received command and returns status
*******************************************************************************/
uint8 ExecuteCommand(uint32 cmd)
{
    uint8 status;

    status = STS_CMD_DONE;

    /* Execute received command */
    switch (cmd)
    {
        case CMD_SET_RED:
            RGB_LED_ON_RED;
            break;

        case CMD_SET_GREEN:
            RGB_LED_ON_GREEN;
            break;

        case CMD_SET_BLUE:
            RGB_LED_ON_BLUE;
            break;

        case CMD_SET_OFF:
            RGB_LED_OFF;
            break;

        default:
            status = STS_CMD_FAIL;
        break;
    }

    return(status);
}


/* [] END OF FILE */
