#ifndef _PWM_H_
#define _PWM_H_

#define PWM_PDCNT_VAL           300         
#define TM1_VALUE               0xFFFA      

typedef enum 
{
    E_RISING_EDGE = 0,   //Rising 
    E_FALLING_EDGE,      //Falling
    E_PWM_MODE_END
} E_PWM_EDGE_MODE;

typedef enum 
{
    PWM_BRAKE_PIN_0 = 0,
    PWM_BRAKE_PIN_1,
    PWM_BRAKE_PIN_2,
    PWM_BRAKE_PIN_3,
    PWM_BRAKE_PIN_4,
    PWM_BRAKE_PIN_5,
    PWM_BRAKE_PIN_MAX
} E_PWM_BRAKE_PIN_SEL;

typedef enum 
{
    PWM_INT_PAIR_0 = 0,
    PWM_INT_PAIR_1,
    PWM_INT_PAIR_2,
    PWM_INT_PAIR_3,
    PWM_INT_PAIR_MAX
} E_PWM_INT_PAIR;

typedef enum 
{
    PWM_INT_TYPE_0 = 0,
    PWM_INT_TYPE_1,
    PWM_INT_TYPE_2,
    PWM_INT_TYPE_3,
    PWM_INT_TYPE_MAX
} E_PWM_INT_TYPE;

typedef enum
{
    PWM_MASK_PIN_0 = 0,
    PWM_MASK_PIN_1,
    PWM_MASK_PIN_2,
    PWM_MASK_PIN_3,
    PWM_MASK_PIN_4,
    PWM_MASK_PIN_5,
    PWM_MASK_PIN_6,
    PWM_MASK_PIN_7,
    PWM_MASK_PIN_MAX
} E_PWM_MASK_PIN_SEL;

typedef enum
{
    PWM_PIN_0 = 0,
    PWM_PIN_1,
    PWM_PIN_2,
    PWM_PIN_3,
    PWM_PIN_4,
    PWM_PIN_5,
    PWM_PIN_6,
    PWM_PIN_7,
    PWM_PIN_MAX
} E_PWM_PIN;

typedef enum
{
    PWM_MODE_0 = 0,
    PWM_MODE_1,
    PWM_MODE_2,
    PWM_MODE_3,
    PWM_MODE_MAX
} E_PWM_MODE;

typedef enum
{
    PWM_DIV_SEL_0 = 0,
    PWM_DIV_SEL_1,
    PWM_DIV_SEL_2,
    PWM_DIV_SEL_3,
    PWM_DIV_SEL_4,
    PWM_DIV_SEL_5,
    PWM_DIV_SEL_6,
    PWM_DIV_SEL_7,
    PWM_CLK_DIV_SEL_MAX
} E_PWM_CLK_DIV_SEL;

void PWM_Brake_Enable (UINT8 Enable);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Brake EDGE mode
 ******************************************************************************/
void PWM_Brake_Edge_Mode (E_PWM_EDGE_MODE EdgeMode);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Brake Pin enable
 ******************************************************************************/
void PWM_Brake_Pin_Enable (E_PWM_BRAKE_PIN_SEL PwmBrakePinSel);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Brake Pin enable
 ******************************************************************************/
void PWM_Brake_Pin_Disable (E_PWM_BRAKE_PIN_SEL PwmBrakePinSel);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Brake Control
 ******************************************************************************/
void PWM_Brake_Control (UINT8 Enable,
                        E_PWM_EDGE_MODE EdgeMode,
                        E_PWM_BRAKE_PIN_SEL PwmBrakePinSel);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Interrupt Pair Selection
 ******************************************************************************/
void PWM_Interrupt_Pair_Sel (E_PWM_INT_PAIR PwmPinSel);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Interrupt Type Selection
 ******************************************************************************/
void PWM_Interrupt_Type_Sel (E_PWM_INT_TYPE PwmPinType);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Mask Pin Selection
 ******************************************************************************/
void PWM_Mask_Pin_Sel (E_PWM_MASK_PIN_SEL PwmMaskPin, UINT8 DataEnable);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Dead Time
 ******************************************************************************/
void PWM_Dead_Time_Control (UINT8 PwmPairPinSel);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Type Select
 ******************************************************************************/
void PWM_Mode_Select (E_PWM_MODE mode);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Polarity Select
 ******************************************************************************/
void PWM_Polarity_Select (E_PWM_PIN PwmPinSel, UINT8 PwmPol);

//------------------------------------------------------------------------------
void Trigger_Timer1(void);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Clock Source Select
 ******************************************************************************/
void PWM_Clock_Select (UINT8 PwmClkSel);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Type Select
 ******************************************************************************/
void PWM_Type_Select (UINT8 PwmTyp);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Group Mode Enable/Disable
 ******************************************************************************/
void PWM_Group_Mode (UINT8 PwmGrp);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Pin Select
 ******************************************************************************/
void PWM_Pin_Select (E_PWM_PIN PwmPinSel);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Interrupt Enable
 ******************************************************************************/
void PWM_Interrupt_Enable (UINT8 Enable);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Brake Interrupt Enable
 ******************************************************************************/
void PWM_Brake_Interrupt_Enable (UINT8 Enable);

/******************************************************************************
 * FUNCTION_PURPOSE: PWM Clock Divider Select
 ******************************************************************************/
void PWM_DIV_Select (E_PWM_CLK_DIV_SEL PwmDivSel);

#endif
