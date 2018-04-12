/*******************************************************************************
* File: main.c
*
* Version: 1.0
*
* Description:
*  This is the source code for an example project that demonstrates basic
*  functionality of the Software Transmit UART component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#include <device.h>

#define SW_UART_PORT        (0u)
#define SW_UART_PIN         (1u)


void main()
{
    uint8 dataArray[]={ 0x44u, 0x61u, 0x74u, 0x61u, 0x41u, 0x72u, 0x72u, 0x61u, 0x79u, 0x5Bu, 0x31u, 0x32u, 0x5Du };
    /*                   D      a      t      a      A      r      r      a      y      [      1      2      ]    */

    LCD_Start();
    LCD_ClearDisplay();
    LCD_Position(0u,0u);
    LCD_PrintString("SW Tx UART demo");
    LCD_Position(1u,0u);
    LCD_PrintString("BaudRate: 115200");
    
    SW_Tx_UART_StartEx(SW_UART_PORT, SW_UART_PIN);
    
    for(;;)
    {
        SW_Tx_UART_PutString("Software Transmit UART");
        SW_Tx_UART_PutString(" component demo");
        SW_Tx_UART_PutCRLF();
        
        SW_Tx_UART_PutString("Sending 254 as single byte hex: ");
        SW_Tx_UART_PutHexByte((uint8)254u);
        SW_Tx_UART_PutCRLF();
        
        SW_Tx_UART_PutString("Sending 65534 as two byte hex: ");
        SW_Tx_UART_PutHexInt((uint16)65534u);
        SW_Tx_UART_PutCRLF();
        
        SW_Tx_UART_PutString("Sending array: ");
        SW_Tx_UART_PutArray(dataArray,13u);
        SW_Tx_UART_PutCRLF();
        
        CyDelay(3000u);
        
        SW_Tx_UART_PutCRLF();
    }
    
}

/* [] END OF FILE */
