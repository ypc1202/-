/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2015 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp.
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/21/2015
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E885 Access SPI Flash (W25Q16BV) demo code
//***********************************************************************************************************

#include <stdio.h>
#include <intrins.h>
#include <string.h>
#include "Common.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------
//
//<e0> System Clock Source Configuration
// <o1> System Clock Source Selection
//      <0=> 2~25MHz    XTAL
//      <1=> 32.768KHz  XTAL
//      <2=> 22.1184MHz Internal
//      <3=> 10KHz      Internal
//      <4=> OSC-In     External
//</e>
//
//<e2> Clock Divider Configuration
//     <o3.0..7>  System Clock Source Devider <1-255>
//                     <i> Fsys = (System Clock Source) / (2 * Devider)
//</e>
//
// <o4> SPI Clock Rate Selection (11.0592MHz System Clock)
//                  <0=>  2.7648MHz, Fosc/4
//                  <1=>  1.3824MHz, Fosc/8
//                  <2=>  0.6912MHz, Fosc/16
//                  <3=>  0.3456MHz, Fosc/32
//-------- <<< end of configuration section >>> ------------------------------
*/

//-----------------------------------------------------------------------------------------------------------
void SPI_Error(void)
{
    printf ("\n*  SPI Error, please check the connection between MCU and SPI Flash");
}
//-----------------------------------------------------------------------------------------------------------
void SPI_Initial(UINT8 SpiClk)
{
    if(SpiClk == 0)
    {
        clr_SPR1;
        clr_SPR0;
    }
    else if(SpiClk == 1)
    {
        clr_SPR1;
        set_SPR0;
    }
    else if(SpiClk == 2)
    {
        set_SPR1;
        clr_SPR0;
    }
    else
    {
        set_SPR1;
        set_SPR0;
    }

    /* /SS General purpose I/O ( No Mode Fault ) */
    set_DISMODF;
    clr_SSOE;

    /* SPI in Master mode */
    set_MSTR;

    /* MSB first */
    clr_LSBFE;

    clr_CPOL;
    clr_CPHA;

    /* Enable SPI function */
    set_SPIEN;
}

//-----------------------------------------------------------------------------------------------------------
void Read_MID_DID(UINT8 *pu8MID, UINT8 *pu8DID)
{
    SS_PIN = 0;
    SPDR = 0x90;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    SPDR = 0xFF;
    while((SPSR&0x80)==0x00);
    *pu8MID = SPDR;
    clr_SPIF;

    SPDR = 0xFF;
    while((SPSR&0x80)==0x00);
    *pu8DID = SPDR;
    clr_SPIF;
    SS_PIN = 1;
}

//-----------------------------------------------------------------------------------------------------------
void Flash_Write_Enable(void)
{
    SS_PIN = 0;
    SPDR = WRITE_ENABLE;
    while((SPSR&0x80)==0x00);
    clr_SPIF;
    SS_PIN = 1;
}

//-----------------------------------------------------------------------------------------------------------
void Flash_Write_Disable(void)
{
    SS_PIN = 0;
    SPDR = WRITE_DISABLE;
    while((SPSR&0x80)==0x00);
    clr_SPIF;
    SS_PIN = 1;
}

//-----------------------------------------------------------------------------------------------------------
void Flash_Chip_Erase(void)
{
    SS_PIN = 0;
    SPDR = CHIP_ERASE;
    while((SPSR&0x80)==0x00);
    clr_SPIF;
    SS_PIN = 1;
}

//-----------------------------------------------------------------------------------------------------------
void Flash_Read_Status(void)
{
    UINT8 u8Status;

    SS_PIN = 0;
    do
    {
        SPDR = READ_STATUS1;
        while((SPSR&0x80)==0x00);
        clr_SPIF;

        SPDR = 0xFF;
        while((SPSR&0x80)==0x00);
        u8Status = SPDR;
        clr_SPIF;
    }
    while((u8Status&0x01)==0x01);
    SS_PIN = 1;
}

//-----------------------------------------------------------------------------------------------------------
void Flash_Erase_Verify(void)
{
    UINT16 u16CNT;
    UINT8  u8Data;

    SS_PIN = 0;

    SPDR = READ_DATA;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    /* 24-bit Address */
    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    for(u16CNT = 0; u16CNT < CHIP_SIZE; u16CNT++)
    {
        SPDR = 0x00;
        while((SPSR&0x80)==0x00);
        u8Data = SPDR;
        clr_SPIF;
        if(u8Data != 0xFF)
        {
            SPI_Error();
        }
    }

    SS_PIN = 1;
}

//-----------------------------------------------------------------------------------------------------------
void Flash_Program(UINT16 *pu16DAT)
{
    SS_PIN = 0;

    SPDR = PAGE_PROGRAM;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    /* 24-bit Address */
    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    /* Send the data to SPI_Flash buffer */
    SPDR = (UINT8)(&pu16DAT);
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    SS_PIN = 1;
}
//-----------------------------------------------------------------------------------------------------------
void Flash_Program_Verify(UINT16 *pu16DAT)
{
    UINT8  u8Data;

    SS_PIN = 0;

    SPDR = READ_DATA;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    /* 24-bit Address */
    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    clr_SPIF;

    SPDR = 0x00;
    while((SPSR&0x80)==0x00);
    u8Data = SPDR;
    clr_SPIF;
    if(u8Data != (UINT8)(&pu16DAT))
    {
        SPI_Error();
    }

    SS_PIN = 1;
}
