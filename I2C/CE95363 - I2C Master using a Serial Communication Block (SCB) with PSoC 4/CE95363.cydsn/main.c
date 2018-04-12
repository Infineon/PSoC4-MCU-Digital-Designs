/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  This example project demonstrates the basic operation of the I2C master
*  (SCB mode) component. The I2C master sends a packet with a command to
*  the I2C slave to control the RGB LED color. The packet with a status
*  is read back.
*  For more information refer to the example project datasheet.
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

#include "project.h"
#include "header.h"


/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  The main function performs the following actions:
*   1. Turns off the RGB LED.
*   2. Starts the I2C master (SCB mode) component.
*   3. Enables global interrupts.
*   4. Sends command and status packets to the slave every 500mS.
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
    uint8 command = CMD_SET_RED;

    RGB_LED_OFF;

    I2CM_Start();

    CyGlobalIntEnable;

    /***************************************************************************
    * Main polling loop
    ***************************************************************************/
    for(;;)
    {
        if (0u == WriteCommandPacket(command))
        {
            if (0u == ReadStatusPacket())
            {
                command++;                  /* Next command to be written */
                if(command > CMD_SET_BLUE)
                {
                    command = CMD_SET_OFF;
                }

                RGB_LED_OFF;                /* Turn off status LED  */
            }
        }

        CyDelay(500u); /* Send command to the I2C slave every 500mS */
    }
}


/*******************************************************************************
* WriteCommandPacket(): Writes command packet to I2C slave
*******************************************************************************/
uint32 WriteCommandPacket(uint8 cmd)
{
    uint8  buffer[BUFFER_SIZE];
    uint32 status = TRANSFER_ERROR;

    /* Initialize buffer with packet */
    buffer[PACKET_SOP_POS] = PACKET_SOP;
    buffer[PACKET_CMD_POS] = cmd;
    buffer[PACKET_EOP_POS] = PACKET_EOP;

    (void) I2CM_I2CMasterWriteBuf(I2C_SLAVE_ADDR, buffer, PACKET_SIZE, I2CM_I2C_MODE_COMPLETE_XFER);

    while (0u == (I2CM_I2CMasterStatus() & I2CM_I2C_MSTAT_WR_CMPLT))
    {
        /* Waits until master completes write transfer */
    }

    /* Displays transfer status */
    if (0u == (I2CM_I2C_MSTAT_ERR_XFER & I2CM_I2CMasterStatus()))
    {
        RGB_LED_ON_GREEN;

        /* Check if all bytes was written */
        if(I2CM_I2CMasterGetWriteBufSize() == BUFFER_SIZE)
        {
            status = TRANSFER_CMPLT;
        }
    }
    else
    {
        RGB_LED_ON_RED;
    }

    (void) I2CM_I2CMasterClearStatus();

    return (status);
}


/*******************************************************************************
* ReadStatusPacket(): Reads status packet from I2C slave
*******************************************************************************/
uint32 ReadStatusPacket(void)
{
    uint8  buffer[BUFFER_SIZE];
    uint32 status = TRANSFER_ERROR;

    (void) I2CM_I2CMasterReadBuf(I2C_SLAVE_ADDR, buffer, PACKET_SIZE, I2CM_I2C_MODE_COMPLETE_XFER);

    while (0u == (I2CM_I2CMasterStatus() & I2CM_I2C_MSTAT_RD_CMPLT))
    {
        /* Waits until master complete read transfer */
    }

    /* Displays transfer status */
    if (0u == (I2CM_I2C_MSTAT_ERR_XFER & I2CM_I2CMasterStatus()))
    {
        RGB_LED_ON_GREEN;

        /* Check packet structure */
        if ((I2CM_I2CMasterGetReadBufSize() == BUFFER_SIZE) &&
            (PACKET_SOP == buffer[PACKET_SOP_POS]) &&
            (PACKET_EOP == buffer[PACKET_EOP_POS]))
        {
            /* Check packet status */
            if (STS_CMD_DONE == buffer[PACKET_STS_POS])
            {
                status = TRANSFER_CMPLT;
            }
        }
    }
    else
    {
        RGB_LED_ON_RED;
        status = TRANSFER_ERROR;
    }

    (void) I2CM_I2CMasterClearStatus();

    return (status);
}


/* [] END OF FILE */
