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
//  File Function: N76E885 PWM Output demo code
//***********************************************************************************************************

#include <stdio.h>
#include "Common.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------
//
//<e0> System Clock Source Configuration
//      <o1> System Clock Source Selection
//          <0=> 2~25MHz    XTAL
//          <1=> 32.768KHz  XTAL
//          <2=> 22.1184MHz Internal
//          <3=> 10KHz      Internal
//          <4=> OSC-In     External
//</e>
//
//<e2> Clock Divider Configuration
//      <o3.0..7>  System Clock Source Devider <1-255>
//          <i> Fsys = (System Clock Source) / (2 * Devider)
//</e>
//
//<h> PWM Option
//     <o4.0..2> PWM Pin Selection
//          <0=> PWM0 (P10) <1=> PWM1 (P11) <2=> PWM2 (P02) <3=> PWM3 (P03)
//          <4=> PWM4 (P05) <5=> PWM5 (P06) <6=> All        <7=> None
//
//      <o18.0..0> PWM Clock Source Selection
//          <0=>  Fpwm = Fsys          <1=>  Fpwm = Timer1 overflow
//      <o20.0..15>  Timer1 Counter Value <0x0000-0xFFFF>
//
//      <o5.0..2> PWM Divider Selection
//          <0=> Fpwm/1  <1=> Fpwm/2   <2=> Fpwm/4   <3=> Fpwm/8
//          <4=> Fpwm/16 <5=> Fpwm/32  <6=> Fpwm/64  <7=> Fpwm/128
//
//      <o6.0..0> PWM Type Selection
//          <0=>  Edge-aligned         <1=>  Center-aligned
//
//      <o16.0..0> PWM Polarity Selection
//          <0=>  Directly output      <1=>  Inversely output
//
//      <o7.0..1> PWM Mode Selection
//          <0=>  Independent
//          <1=>  Complementary
//          <2=>  Synchronized
//
//      <e8>  PWM Dead-time Enable in Independent Mode
//          <o9.0..1> PWM pair dead-time insertion Selection
//              <0=>  PWM0/1 pair dead-time insertion enable
//              <1=>  PWM2/3 pair dead-time insertion enable
//              <2=>  PWM4/5 pair dead-time insertion enable
//              <3=>  All PWM
//          <o10.0..8>  PWM Dead-time Counter  <0-511>
//              <i> PWM dead-time = (PDTCNT + 1) / Fsys
//      </e>
//
//      <e17>  PWM Mask Enable
//          <o11.0..2> PWM Mask Pin Selection
//              <0=> PWM0 (P10) <1=> PWM1 (P11) <2=> PWM2 (P02) <3=> PWM3 (P03)
//              <4=> PWM4 (P05) <5=> PWM5 (P06) <6=> All        <7=> None
//          <o12.0..0> PWM Mask Data
//              <0=>  Masked by 0   <1=>  Masked by 1
//      </e>
//
//      <e13>  PWM Brake Enable
//          <o25.0..2> PWM Pin Selection
//              <0=> PWM0 (P10) <1=> PWM1 (P11) <2=> PWM2 (P02) <3=> PWM3 (P03)
//              <4=> PWM4 (P05) <5=> PWM5 (P06) <6=> All
//          <o14.0..0> PWM Brake pin input level selection
//              <0=> P2.3 Falling edge  <1=>  P2.3 Rising edge
//          <o15.0..0> PWM Brake Data
//              <0=> 0          <1=> 1
//          <e24>  PWM Brake Interrupt Enable
//          </e>
//      </e>
//
//      <e19>  PWM Group Enable
//      </e>
//
//      <e23>  PWM Interrupt Enable
//          <o21.0..1> PWM Interrupt Type Selection
//              <0=>  Falling edge on PWM0/2/4 pin
//              <1=>  Rising edge on PWM0/2/4 pin
//              <2=>  Central point of a PWM period
//              <3=>  End point of a PWM period
//
//          <o22.0..1> PWM Interrupt Pair Selection
//              <0=>  PWM0
//              <1=>  PWM2
//              <2=>  PWM4
//              <3=>  PWM4
//      </e>
//
//</h>
//
//-------- <<< end of configuration section >>> ------------------------------
*/

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Brake Enable
 ******************************************************************************/
void PWM_Brake_Enable (UINT8 Enable)
{
    if(Enable)
    {
        set_FBINEN;
    }
    else
    {
        clr_FBINEN;
    }
}

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Brake EDGE mode
 ******************************************************************************/
void PWM_Brake_Edge_Mode (E_PWM_EDGE_MODE EdgeMode)
{
    if(EdgeMode == E_RISING_EDGE)
    {
        set_FBINLS;
    }
    else
    {
        clr_FBINLS;
    }
}

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Brake Pin enable
 ******************************************************************************/
void PWM_Brake_Pin_Enable (E_PWM_BRAKE_PIN_SEL PwmBrakePinSel)
{
    switch(PwmBrakePinSel)
    {
        case PWM_BRAKE_PIN_0:
            set_FBD0;
            break;

        case PWM_BRAKE_PIN_1:
            set_FBD1;
            break;

        case PWM_BRAKE_PIN_2:
            set_FBD2;
            break;

        case PWM_BRAKE_PIN_3:
            set_FBD3;
            break;

        case PWM_BRAKE_PIN_4:
            set_FBD4;
            break;

        case PWM_BRAKE_PIN_5:
            set_FBD5;
            break;

        default:
            break;
    }
}

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Brake Pin enable
 ******************************************************************************/
void PWM_Brake_Pin_Disable (E_PWM_BRAKE_PIN_SEL PwmBrakePinSel)
{
    switch(PwmBrakePinSel)
    {
        case PWM_BRAKE_PIN_0:
            clr_FBD0;
            break;

        case PWM_BRAKE_PIN_1:
            clr_FBD1;
            break;

        case PWM_BRAKE_PIN_2:
            clr_FBD2;
            break;

        case PWM_BRAKE_PIN_3:
            clr_FBD3;
            break;

        case PWM_BRAKE_PIN_4:
            clr_FBD4;
            break;

        case PWM_BRAKE_PIN_5:
            clr_FBD5;
            break;

        default:
            break;
    }
}

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Brake Control
 ******************************************************************************/
void PWM_Brake_Control (UINT8 Enable,
                        E_PWM_EDGE_MODE EdgeMode,
                        E_PWM_BRAKE_PIN_SEL PwmBrakePinSel)
{
    PWM_Brake_Enable(Enable);
    PWM_Brake_Edge_Mode(EdgeMode);

    if(Enable)
    {
        PWM_Brake_Pin_Enable(PwmBrakePinSel);
    }
    else
    {
        PWM_Brake_Pin_Disable(PwmBrakePinSel);
    }
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Interrupt Pair Selection
 ******************************************************************************/
void PWM_Interrupt_Pair_Sel (E_PWM_INT_PAIR PwmPinSel)
{
    switch(PwmPinSel)
    {
        case PWM_INT_PAIR_0:
        {
            clr_INTSEL1;
            clr_INTSEL0;
        }
        break;

        case PWM_INT_PAIR_1:
        {
            clr_INTSEL1;
            set_INTSEL0;
        }
        break;

        case PWM_INT_PAIR_2:
        {
            set_INTSEL1;
            clr_INTSEL0;
        }
        break;

        case PWM_INT_PAIR_3:
        {
            set_INTSEL1;
            set_INTSEL0;
        }
        break;

        default:
            break;
    }
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Interrupt Type Selection
 ******************************************************************************/
void PWM_Interrupt_Type_Sel (E_PWM_INT_TYPE PwmPinType)
{
    switch(PwmPinType)
    {
        case PWM_INT_TYPE_0:
        {
            clr_INTTYP1;
            clr_INTTYP0;
        }
        break;

        case PWM_INT_TYPE_1:
        {
            clr_INTTYP1;
            set_INTTYP0;
        }
        break;

        case PWM_INT_TYPE_2:
        {
            set_INTTYP1;
            clr_INTTYP0;
        }
        break;

        case PWM_INT_TYPE_3:
        {
            set_INTTYP1;
            set_INTTYP0;
        }
        break;

        default:
            break;
    }
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Mask Pin Selection
 ******************************************************************************/
void PWM_Mask_Pin_Sel (E_PWM_MASK_PIN_SEL PwmMaskPin, UINT8 DataEnable)
{
    switch(PwmMaskPin)
    {
        case PWM_MASK_PIN_0:
        {
            set_PMEN0;
            if(DataEnable == 1)
            {
                set_PMD0;
            }
            else
            {
                clr_PMD0;
            }
        }
        break;

        case PWM_MASK_PIN_1:
        {
            set_PMEN1;
            if(DataEnable == 1)
            {
                set_PMD1;
            }
            else
            {
                clr_PMD1;
            }
        }
        break;

        case PWM_MASK_PIN_2:
        {
            set_PMEN2;
            if(DataEnable == 1)
            {
                set_PMD2;
            }
            else
            {
                clr_PMD2;
            }
        }
        break;

        case PWM_MASK_PIN_3:
        {
            set_PMEN3;
            if(DataEnable == 1)
            {
                set_PMD3;
            }
            else
            {
                clr_PMD3;
            }
        }
        break;

        case PWM_MASK_PIN_4:
        {
            set_PMEN4;
            if(DataEnable == 1)
            {
                set_PMD4;
            }
            else
            {
                clr_PMD4;
            }
        }
        break;

        case PWM_MASK_PIN_5:
        {
            set_PMEN5;
            if(DataEnable == 1)
            {
                set_PMD5;
            }
            else
            {
                clr_PMD5;
            }
        }
        break;

        case PWM_MASK_PIN_6:
        {
            set_PMEN6;
            if(DataEnable == 1)
            {
                set_PMD6;
            }
            else
            {
                clr_PMD6;
            }
        }
        break;

        case PWM_MASK_PIN_7:
        {
            set_PMEN7;
            if(DataEnable == 1)
            {
                set_PMD7;
            }
            else
            {
                clr_PMD7;
            }
        }
        break;

        default:
            break;
    }
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Dead Time
 ******************************************************************************/
void PWM_Dead_Time_Control (UINT8 PwmPairPinSel)
{
    UINT8 u8Tmp;

    if(PwmPairPinSel == 0)
    {
        set_PDT01EN;
    }
    else if(PwmPairPinSel == 1)
    {
        set_PDT23EN;
    }
    else
    {
        set_PDT45EN;
    }

    TA = 0xAA;
    TA = 0x55;
    PDTEN |= 0x07;
    TA = 0xAA;
    TA = 0x55;
    PDTCNT = LOBYTE(PWM_PDCNT_VAL);
    u8Tmp =  HIBYTE(PWM_PDCNT_VAL);

    if(u8Tmp == 0)
    {
        TA = 0xAA;
        TA = 0x55;
        PDTEN &= CLR_BIT4;
    }
    else
    {
        TA = 0xAA;
        TA = 0x55;
        PDTEN |= SET_BIT4;
    }
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Type Select
 ******************************************************************************/
void PWM_Mode_Select (E_PWM_MODE mode)
{
    switch(mode)
    {
        case PWM_MODE_0:                //Independent Mode
        {
            clr_PWMMOD1;
            clr_PWMMOD0;
        }
        break;

        case PWM_MODE_1:                //Complementary Mode
        {
            clr_PWMMOD1;
            set_PWMMOD0;
        }
        break;

        case PWM_MODE_2:                //Synchronized Mode
        {
            set_PWMMOD1;
            clr_PWMMOD0;
        }
        break;

        case PWM_MODE_3:                //Independent Mode
        {
            clr_PWMMOD1;
            clr_PWMMOD0;
        }
        break;

        default:
            break;
    }
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Polarity Select
 ******************************************************************************/
void PWM_Polarity_Select (E_PWM_PIN PwmPinSel, UINT8 PwmPol)
{
    switch(PwmPinSel)
    {
        case PWM_PIN_0:
        {
            if(PwmPol)
            {
                clr_PNP0;            //directly
            }
            else
            {
                set_PNP0;            //inversely
            }
        }
        break;

        case PWM_PIN_1:
        {
            if(PwmPol)
            {
                clr_PNP1;            //directly
            }
            else
            {
                set_PNP1;            //inversely
            }
        }
        break;

        case PWM_PIN_2:
        {
            if(PwmPol)
            {
                clr_PNP2;            //directly
            }
            else
            {
                set_PNP2;            //inversely
            }
        }
        break;

        case PWM_PIN_3:
        {
            if(PwmPol)
            {
                clr_PNP3;            //directly
            }
            else
            {
                set_PNP3;            //inversely
            }
        }
        break;

        case PWM_PIN_4:
        {
            if(PwmPol)
            {
                clr_PNP4;            //directly
            }
            else
            {
                set_PNP4;            //inversely
            }
        }
        break;

        case PWM_PIN_5:
        {
            if(PwmPol)
            {
                clr_PNP5;            //directly
            }
            else
            {
                set_PNP5;            //inversely
            }
        }
        break;

        case PWM_PIN_6:
        {
            if(PwmPol)
            {
                clr_PNP6;            //directly
            }
            else
            {
                set_PNP6;            //inversely
            }
        }
        break;

        case PWM_PIN_7:
        {
            if(PwmPol)
            {
                clr_PNP7;            //directly
            }
            else
            {
                set_PNP7;            //inversely
            }
        }
        break;

        default:
            break;
    }
}

//------------------------------------------------------------------------------
void Trigger_Timer1(void)
{
    clr_T1M;                                //T1M=0, Timer1 Clock = Fsys/12
    TMOD |= 0x10;                           //Timer1 is 16-bit mode
    TL1 = LOBYTE(TM1_VALUE);
    TH1 = HIBYTE(TM1_VALUE);
    set_TR1;
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Clock Source Select
 ******************************************************************************/
void PWM_Clock_Select (UINT8 PwmClkSel)
{
    if(PwmClkSel)
    {
        set_PWMCKS;
        Trigger_Timer1();
    }
    else
    {
        clr_PWMCKS;
    }
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Type Select
 ******************************************************************************/
void PWM_Type_Select (UINT8 PwmTyp)
{
    if(PwmTyp == 0)                      //Edge-aligned
    {
        clr_PWMTYP;
    }
    else
    {
        set_PWMTYP;        //Center-aligned
    }
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Group Mode Enable/Disable
 ******************************************************************************/
void PWM_Group_Mode (UINT8 PwmGrp)
{
    if(PwmGrp == 0)
    {
        clr_GP;
    }
    else
    {
        set_GP;
    }
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Pin Select
 ******************************************************************************/
void PWM_Pin_Select (E_PWM_PIN PwmPinSel)
{
    switch(PwmPinSel)
    {
        case PWM_PIN_0:
            set_PIO0;                //P1.0 = PWM0
            break;

        case PWM_PIN_1:
            set_PIO1;                //P1.1 = PWM1
            break;

        case PWM_PIN_2:
            set_PIO2;                //P0.2 = PWM2
            break;

        case PWM_PIN_3:
            set_PIO3;                //P0.3 = PWM3
            break;

        case PWM_PIN_4:
            set_PIO4;                //P0.5 = PWM4
            break;

        case PWM_PIN_5:
            set_PIO5;                //P0.6 = PWM5
            break;

        case PWM_PIN_6:
            set_PIO6;
            break;

        case PWM_PIN_7:
            set_PIO7;
            break;

        default:
            PIO &= ~0x3F;               //None, all PWM pin are GPIO mode
            break;
    }
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Interrupt Enable
 ******************************************************************************/
void PWM_Interrupt_Enable (UINT8 Enable)
{
    if(Enable == 1)
    {
        set_EPWM;
        set_EA;
    }
    else
    {
        clr_EPWM;
        clr_EA;
    }
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Brake Interrupt Enable
 ******************************************************************************/
void PWM_Brake_Interrupt_Enable (UINT8 Enable)
{
    if(Enable == 1)
    {
        set_EFB;
        set_EA;
    }
    else
    {
        clr_EFB;
        clr_EA;
    }
}
/******************************************************************************
 * FUNCTION_PURPOSE: PWM Clock Divider Select
 ******************************************************************************/
void PWM_DIV_Select (E_PWM_CLK_DIV_SEL PwmDivSel)
{
    switch(PwmDivSel)
    {
        case PWM_DIV_SEL_0:
        {
            clr_PWMDIV2;
            clr_PWMDIV1;
            clr_PWMDIV0;
        }
        break;

        case PWM_DIV_SEL_1:
        {
            clr_PWMDIV2;
            clr_PWMDIV1;
            set_PWMDIV0;
        }
        break;

        case PWM_DIV_SEL_2:
        {
            clr_PWMDIV2;
            set_PWMDIV1;
            clr_PWMDIV0;
        }
        break;

        case PWM_DIV_SEL_3:
        {
            clr_PWMDIV2;
            set_PWMDIV1;
            set_PWMDIV0;
        }
        break;

        case PWM_DIV_SEL_4:
        {
            set_PWMDIV2;
            clr_PWMDIV1;
            clr_PWMDIV0;
        }
        break;

        case PWM_DIV_SEL_5:
        {
            set_PWMDIV2;
            clr_PWMDIV1;
            set_PWMDIV0;
        }
        break;

        case PWM_DIV_SEL_6:
        {
            set_PWMDIV2;
            set_PWMDIV1; 
            clr_PWMDIV0;
        }
        break;

        case PWM_DIV_SEL_7:
        {
            set_PWMDIV2;
            set_PWMDIV1;
            set_PWMDIV0;
        }
        break;
    }
}
