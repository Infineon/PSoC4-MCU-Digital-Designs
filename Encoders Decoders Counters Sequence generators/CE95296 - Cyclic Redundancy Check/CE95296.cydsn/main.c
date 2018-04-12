/*******************************************************************************
* File Name: main.c
*
* Version: 2.1
*
* Description:
*  This is source code for Example Project of the CRC component.
*  Parameters used:
*   Standard Polynomial - CRC-16
*   Resolution          - 16 bits
*   Implementation      - Single Cycle 
*   Polynomial Value    - 0xC002
*   Seed Value          - 0x0000
*
* This project consists of 16 bits CRC (in the Single Cycle Implementation Mode).
* Clock signal generated by the control register "Clock_Gen".
* Reset signal generated by the control register "Reset_Gen".
* CRC consistently execute some calculation (SEED_VALUE_COUNT define). 
* It value displayed on LCD and named: CRC.
* Software calculated value output on LCD for verification (SV).
* After calculation is finished reset of the CRC are execute. 
* Value after reset is displayed on LCD and named: CRC.
* All signals changes can see on oscillator or signal analyzer at PORT3 [2:0] by default.
* 
* Defines:
* SEED_VALUE_COUNT - set number of CRC calculate iteration. (20 by default)
* DISP_DELAY - set delay of information on the LCD. (1000 by default)
* in - input data signal (1 by default for software CRC calculation).
* 
* LCD view:
* SV = Software calculated CRC value.
* Calc = Hardware calculated CRC iteration at this time.
* CRC = Hardware calculated CRC value for current iteration.
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

#define DISP_DELAY          (1000u)     /* Display delay */
#define SEED_VALUE_COUNT    (20u)       /* Iteration amount */
#define in                     (1u)        /* Data input software value */

/*******************************************************************************
* Function Name: Clock1
********************************************************************************
*
* Summary:
*  Generate clock signal.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Clock1(void)
{
    Clock_Gen_Write(1u);
    CyDelay(1u);
    Clock_Gen_Write(0u);
    CyDelay(1u);
}


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function performs following functions:
*   1. Generate Clock signals
*   2. Generate Reset signals
*   3. Execute software CRC calculation
*   4. Prints CRC calculated values on LCD.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void main()
{
    uint16 CRC_val = 0u;
    uint16 seed, poly, seed_msb, int_xor_1, int_xor_res, and_op, xor_op;
    uint8 i;

        /* Initialization delay */
        CyDelay(50);

        /* Enable global interrupts. */
        CyGlobalIntEnable;    

    /* Initialization */    
    Reset_Gen_Write(0u);
    Clock_Gen_Write(0u);
        LCD_Start();
    CRC_Start();

    LCD_Position(0u,0u);
    LCD_PrintString("CRC16");
    LCD_Position(1u,0u);
    LCD_PrintString("Example Project");
    CyDelay(DISP_DELAY*3u);
    LCD_ClearDisplay();
    
    /* Software CRC value calculation */    
    CRC_val = CRC_ReadCRC();
    poly = CRC_ReadPolynomial();
    seed = CRC_val; 
    seed_msb = CRC_val;
    for (i=0; i<SEED_VALUE_COUNT; i++)
    {
        seed_msb = seed_msb >> (CRC_CRC_SIZE - 1);
        seed_msb = seed_msb & 1u;
        int_xor_1 = seed_msb ^ in;

        if (int_xor_1 == 1u) 
        {
            int_xor_res = 0xffffu; 
        }
        else 
        {
            int_xor_res = 0u; 
        }
        
        and_op = int_xor_res & poly;
        xor_op = seed ^ and_op;
        seed = xor_op << 1u;
        seed = seed | int_xor_1;
        seed_msb = seed;
        seed &= CRC_MASK;
    }
    
    /* Display Software calculated crc value on LCD */
    LCD_Position(0u,0u);
    LCD_PrintString("SV=");
    LCD_PrintInt16(seed);    
    CyDelay(DISP_DELAY);

    /* Display Hardware calculated crc value and current iteration on LCD */
    for (i=0; i<=SEED_VALUE_COUNT; i++) 
    {
        LCD_Position(0u,9u);
        LCD_PrintString("Calc=");
        LCD_PrintNumber(i);
        LCD_Position(1u,0u);
        LCD_PrintString("CRC=");
        LCD_PrintInt16(CRC_ReadCRC());
        CyDelay(DISP_DELAY);

        /* Execute calculations */
        Clock1();
    }
    
    /* Clear display after delay */
    CyDelay(DISP_DELAY * 3u);
    LCD_ClearDisplay();
    
    LCD_Position(0u,0u);
    LCD_PrintString("Reset CRC....");
    CyDelay(DISP_DELAY * 3u);
    LCD_ClearDisplay();
    
    /* CRC reset */
    Reset_Gen_Write(1u);
    CyDelay(1u);
    Clock1();

    LCD_Position(0u,0u);
    LCD_PrintString("CRC after Reset:");

    /* Display CRC values after reset and initialization */
    LCD_Position(1u,0u);
    LCD_PrintString("CRC=");
    LCD_PrintInt16(CRC_ReadCRC());

    /* Empty cycle*/
    for (;;) 
    {
    }
}


/* [] END OF FILE */
