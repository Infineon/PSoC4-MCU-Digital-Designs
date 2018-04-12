/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  This is the source code for the datasheet example of the Count7 component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include <device.h>


/*********************/
/* #define constants */
/*********************/
#define COUNTERS_ENABLED      (1u)
#define ENABLE_MASK           (0xFEu)

#define COUNTERS_LOAD         (2u)
#define LOAD_MASK             (0xFDu)


/******************************/
/* ISR prototype declarations */
/******************************/
CY_ISR_PROTO(Enable_int);
CY_ISR_PROTO(Load_int);


/*******************************************************************************
* Function Name: Load_int
********************************************************************************
*
* Summary:
*  ISR for handling Load signal.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
CY_ISR(Load_int)
{
    /* Clear SW2 pin interrupt */
    SW2_ClearInterrupt();
    
    if(COUNTERS_LOAD == (Control_Read() & COUNTERS_LOAD))
    {
        /* Clear load signal that comes from the control register. This will start
        * Count7 operation.
        */
        Control_Write(Control_Read() & LOAD_MASK);
    }
    else
    {
        /* Set load signal in the control register. The counter will be 
        * continuously loaded with period value.
        */
        Control_Write(Control_Read() | COUNTERS_LOAD);
    }
    
    
    /* Adds the delay to avoid false button press */
    CyDelay(100u);
}


/*******************************************************************************
* Function Name: Enable_int
********************************************************************************
*
* Summary:
*  ISR for handling Enable signal.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
CY_ISR(Enable_int)
{
    /* Clear SW2 pin interrupt */
    SW1_ClearInterrupt();
    
    if(COUNTERS_ENABLED == (Control_Read() & COUNTERS_ENABLED))
    {
        /* Clear enable signal that comes from the control register */
        Control_Write(Control_Read() & ENABLE_MASK);
    }
    else
    {
        /* Set the enable signal in the control register */
        Control_Write(Control_Read() | COUNTERS_ENABLED);
    }
    
    /* Adds a delay to avoid a false button press */
    CyDelay(100u);
}


/*******************************************************************************
* Function Name: StartProcedure
********************************************************************************
*
* Summary:
*  Performs start procedure for the Count7.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void StartProcedure(void)
{
    LCD_Position(0u, 0u);
    LCD_PrintString("Starting Count7...");
    
    /* Set Enable and Load signals High to load the period into
    * The COUNT register.
    */
    Control_Write(COUNTERS_ENABLED | COUNTERS_LOAD);
    
    /* Wait for no less than one cycle of the input clock to start the Count7 */
    CyDelay(800u);
    
    /* Clear Load signal */
    Control_Write(COUNTERS_ENABLED);
    
    /* The start of Count7 is done so display the message on the LCD */
    LCD_Position(1u, 0u);
    LCD_PrintString("Done...");
    
    /* Delay to see the message on the LCD */
    CyDelay(500u);
}


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  The main function of the Count7 example project.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void main()
{
    CyGlobalIntEnable;  /* Enable global interrupts. */
    
    /********************/
    /* Interrupts setup */
    /********************/
    sw1_Isr_StartEx(Enable_int);
    sw2_Isr_StartEx(Load_int);
    
    /* Start the LCD and Count7 */
    Count7_Start();
    LCD_Start();
    
    /* Run the start procedure */
    StartProcedure();
    
    while(1u)
    {
        /* Clear the display */
        LCD_ClearDisplay();
          
        LCD_Position(0u, 0u);
        LCD_PrintString("COUNT  :");
        
        /* Stop the Count7 prior to reading COUNT register */
        Count7_Stop();
        /* Read and display the content of the COUNT register of Count7 */
        LCD_PrintInt8(Count7_ReadCounter());
        /* Start the Count7 */
        Count7_Start();
        
        /* Display the content of the status register */
        LCD_Position(1u, 0u);
        LCD_PrintString("Status :");
        LCD_PrintInt8(Status_Read());
        
        LCD_Position(0u, 12u);
        
        if(COUNTERS_ENABLED == (Control_Read() & COUNTERS_ENABLED))
        {
            /* Count7 is enabled */
            LCD_PrintString("EN");
        }
        else 
        {
            /* Count7 is disabled */
            LCD_PrintString("DIS");
        }
        
        LCD_Position(1u, 12u);
        
        if(COUNTERS_LOAD == (Control_Read() & COUNTERS_LOAD))
        {
            /* The Count7 is hold in the LOAD state */
            LCD_PrintString("LD");
        }
        else
        {
            /* The Count7 is not hold in the LOAD state */
            LCD_PrintString("RUN");
        }
            
            /* Delay to make the data visible */
            CyDelay(300u);
    }
}

/* [] END OF FILE */

