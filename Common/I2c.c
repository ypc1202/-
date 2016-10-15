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
//  File Function: N76E885 I2C demo code, Slave Address of 24LC64 = 0xA0
//
//   ____________           ______________
//  |            |   SDA    |             |
//  |            |<-------->|             |
//  |            |          |             |
//  |N76E885(M) |          |   24LC64(S) |
//  |            |   SCL    |             |
//  |            |--------->|             |
//  |____________|          |_____________|
//
//  Microchip I2C EEPROM 24xx64 (64K Bit) is used as the slave device.
//  The page size are 32Byte. Total are 256 page.
//  If verification passes, Port3 will show 0x78. If there is any failure
//  occured during the progress, Port3 will show 0x00.
//***********************************************************************************************************
#include <stdio.h>
#include "Common.h"
/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------
//
////<e0> System Clock Source Configuration
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
// <o3> I2C Clock Rate Selection (11.0592MHz System Clock)
//                  <27=> 100kbps
//                  <6=>  400kbps
//                  <2=>  1Mbps
//-------- <<< end of configuration section >>> ------------------------------
*/
//========================================================================================================
void Init_I2C(void)
{
    /* Set I2C clock rate */
    I2CLK = I2C_CLOCK;
    /* Enable I2C */
    set_I2CEN;
}
//========================================================================================================
void One_Page_Read(UINT8 u8PageNumber, UINT8 u8DAT)
{
    UINT8  u8Count;
    UINT16 u16Address;
    u16Address = (UINT16)u8PageNumber * 32;
    /* Step1 */
    set_STA;                                /* Send Start bit to I2C EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
    {
        printf("\nI2C 'Send STA' error");
    }
    /* Step2 */
    I2DAT = (EEPROM_SLA | EEPROM_WR);       /* Send (SLA+W) to EEPROM */
    clr_STA;                                /* Clear STA and Keep SI value in I2CON */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x18)                     /* 0x18: SLA+W has been transmitted; ACK has been received */
    {
        printf("\nI2C 'Send SLA+W' error");
    }
    /* Step3 */
    I2DAT = HIBYTE(u16Address);             /* Send I2C EEPROM's High Byte Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        printf("\nI2C 'Send I2C High Byte Address' error");
    }
    /* Step4 */
    I2DAT = LOBYTE(u16Address);             /* Send I2C EEPROM's Low Byte Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        printf("\nI2C 'Send I2C Low Byte Address' error");
    }
    /* Step5 */
    set_STA;                                /* Repeated START */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x10)                     /* 0x10: A repeated START condition has been transmitted */
    {
        printf("\nI2C 'Send STA' error");
    }
    /* Step6 */
    clr_STA;                                /* Clear STA and Keep SI value in I2CON */
    I2DAT = (EEPROM_SLA | EEPROM_RD);       /* Send (SLA+R) to EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x40)                     /* 0x40:  SLA+R has been transmitted; ACK has been received */
    {
        printf("\nI2C 'Send SLA+R' error");
    }
    /* Step7 */                             /* Verify I2C EEPROM data */
    for (u8Count = 0; u8Count <PAGE_SIZE; u8Count++)
    {
        set_AA;                             /* Set Assert Acknowledge Control Bit */
        clr_SI;
        while (!SI);
        if (I2STAT != 0x50)                 /* 0x50:Data byte has been received; NOT ACK has been returned */
        {
            printf("\nI2C 'No Ack' error");
        }
        if (I2DAT != u8DAT)                 /* Send the Data to EEPROM */
        {
            printf("\nI2C 'Read data' error");
        }
        u8DAT = ~u8DAT;
    }
    /* Step8 */
    clr_AA;                                 /* Send a NACK to disconnect 24xx64 */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x58)                     /* 0x58:Data byte has been received; ACK has been returned */
    {
        printf("\nI2C 'Ack' error");
    }
    /* Step9 */
    clr_SI;
    set_STO;
    while (STO);                            /* Check STOP signal */
}
//========================================================================================================
void One_Page_Write(UINT8 u8PageNumber, UINT8 u8DAT)
{
    UINT8  u8Count;
    UINT16 u16Address;
    u16Address = (UINT16)u8PageNumber * 32;
    /* Step1 */
    set_STA;                                /* Send Start bit to I2C EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
    {
        printf("\nI2C 'Send STA' error");
    }
    /* Step2 */
    clr_STA;                                /* Clear STA and Keep SI value in I2CON */
    I2DAT = EEPROM_SLA | EEPROM_WR;         /* Send (SLA+W) to EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x18)                     /* 0x18: SLA+W has been transmitted; ACK has been received */
    {
        printf("\nI2C 'Send SLA+W' error");
    }
    /* Step3 */
    I2DAT = HIBYTE(u16Address);             /* Send EEPROM's High Byte Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        printf("\nI2C 'Send High byte address' error");
    }
    /* Step4 */
    I2DAT = LOBYTE(u16Address);             /* Send EEPROM's Low Byte Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        printf("\nI2C 'Send Low byte address' error");
    }
    /* Step5 */
    /* Write data to I2C EEPROM */
    for (u8Count = 0; u8Count < PAGE_SIZE; u8Count++)
    {
        I2DAT = u8DAT;                      /* Send data to EEPROM */
        clr_SI;
        while (!SI);
        if (I2STAT != 0x28)                 /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
        {
            printf("\nI2C 'Write Data' error");
        }
        u8DAT = ~u8DAT;
    }
    //After STOP condition, a inner EEPROM timed-write-cycle
    //will occure and EEPROM will not response to outside command
    /* 0x18: SLA+W has been transmitted; ACK has been received */
    /* Step6 */
    do
    {
        set_STO;                            /* Set I2C STOP Control Bit */
        clr_SI;
        while (STO);                        /* Check STOP signal */
        set_STA;                            /* Check if no ACK is returned by EEPROM, it is under timed-write cycle */
        clr_SI;
        while (!SI);
        if (I2STAT != 0x08)                 /* 0x08:  A START condition has been transmitted*/
        {
            printf("\nI2C 'Wait Ready' error");
        }
        clr_STA;                            /* Clear STA and Keep SI value in I2CON */
        I2DAT = (EEPROM_SLA | EEPROM_WR);   /* Send (SLA+W) to EEPROM */
        clr_SI;
        while (!SI);
    }
    while(I2STAT != 0x18);
    /* Step7 */
    set_STO;                                /* Set STOP Bit to I2C EEPROM */
    clr_SI;
    while (STO);                            /* Check STOP signal */
}
