#include "../../Library/STD_TYPES.h"
#include "../../Library/ErrType.h"

#include "util/delay.h"

#include "../../MCAL/Timer/Timer_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/EXTI/EXTI_interface.h"

#include "Ultrasonic_prv.h"
#include "Ultrasonic_cfg.h"
#include "Ultrasonic_interface.h"


static uint32 ICU_HW_u32Reading1 = 0u;
static uint32 ICU_HW_u32Reading2 = 0u;
static volatile uint16 OVF_HW_u16Counter = 0u;

static uint32 ICU_SW_u8Reading1 = 0u;
static uint32 ICU_SW_u8Reading2 = 0u;
static volatile uint32 OVF_SW_u8Counter = 0u;

static ECHO_PINS_t ECHO_PIN = 0;


uint8 Ultrasonic_u8GetDistance(ULTRASONIC_CONFIG_t* Copy_pstConfiguration, uint16* Copy_pu16Distance_mm)
{
	uint8 Local_u8ErrorState = OK;

	if((Copy_pstConfiguration != NULL) && (Copy_pu16Distance_mm != NULL))
	{
		uint16 Local_u16Time_us = 0u;

		DIO_u8SetPinValue(Copy_pstConfiguration->PORT,Copy_pstConfiguration->TRIG_PIN,DIO_u8PIN_HIGH);
		_delay_us(10);
		DIO_u8SetPinValue(Copy_pstConfiguration->PORT,Copy_pstConfiguration->TRIG_PIN,DIO_u8PIN_LOW);

		ECHO_PIN = Copy_pstConfiguration->ECHO_PIN;

		if(Copy_pstConfiguration->ECHO_PIN == ECHO_PD6)
		{

			ICU_voidSetTriggerEvent(ICU_RISING_EDGE);
			Timer_voidInterruptEnable(INT_T1_IC);
			Timer_voidInterruptEnable(INT_T1_OVF);
			Timer_u8SetCallBackFunction(INT_T1_OVF, &Timer1_voidOverflow);
			Timer_u8SetCallBackFunction(INT_T1_IC, &ICU_voidHW);

			Timer1_Config_t Local_stTimer1 =
			{
					.WGM = WGM_NORMAL,
					.CLK = PRESCALER_64,
					.OC_Mode = OC_MODE_DISCONNECT,
			};

			Timer1_u8Init(&Local_stTimer1);

			while((ICU_HW_u32Reading1 == 0) || (ICU_HW_u32Reading2 == 0));

			Local_u16Time_us = ((ICU_HW_u32Reading2 - ICU_HW_u32Reading1) * (CLK_PRESCALER_64 / CPU_FREQ));
		}
		else if(Copy_pstConfiguration->ECHO_PIN == ECHO_PD2)
		{
			Timer1_Config_t Local_stTimer1 =
			{
					.WGM = WGM_NORMAL,
					.CLK = PRESCALER_64,
					.OC_Mode = OC_MODE_DISCONNECT,
			};

			Timer1_u8Init(&Local_stTimer1);


			Timer_voidInterruptEnable(INT_T1_OVF);
			Timer_u8SetCallBackFunction(INT_T1_OVF,&Timer1_voidOverflow);

			EXTI_u8SetSenseCtrl(INT0,RISING_EDGE);
			EXTI_u8EnableIntChannel(INT0);
			EXIT_u8SetCallBack(INT0,&ICU_voidSW);

			while((ICU_SW_u8Reading1 == 0) || (ICU_SW_u8Reading2 == 0));

			Local_u16Time_us = ((ICU_SW_u8Reading2 - ICU_SW_u8Reading1) * (CLK_PRESCALER_64 / CPU_FREQ));
		}

		*Copy_pu16Distance_mm = (uint16)((((uint32)Local_u16Time_us * SOUND_SPEED_mm_PER_ms)/DIVIDE_FACTOR) + 20u);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

static void ICU_voidHW(void)
{
	static volatile uint8 Local_u8Counter = 0;
	Local_u8Counter++;

	if(Local_u8Counter == 1u)
	{
		ICU_HW_u32Reading1 = (uint32)ICU_u16GetReading();
		ICU_voidSetTriggerEvent(ICU_FALLING_EDGE);
	}
	else if(Local_u8Counter == 2u)
	{
		ICU_HW_u32Reading2 = (uint32)ICU_u16GetReading();
		if(OVF_HW_u16Counter > 0)
		{
			ICU_HW_u32Reading2 += (OVF_HW_u16Counter * TIMER1_OVF_TICKS);
			OVF_HW_u16Counter = 0;
		}
		Local_u8Counter = 0;
		ICU_voidSetTriggerEvent(ICU_RISING_EDGE);
		Timer_voidInterruptDisable(INT_T1_IC);
		Timer_voidInterruptDisable(INT_T1_OVF);
	}
	else
	{
		//Do nothing
	}
}

static void Timer1_voidOverflow(void)
{
	switch(ECHO_PIN)
	{
	case ECHO_PD6: OVF_HW_u16Counter++; break;
	case ECHO_PD2:	OVF_SW_u8Counter++;	 break;

	}
}

static void ICU_voidSW(void)
{
	static volatile uint8 Local_u8Counter = 0;
	Local_u8Counter++;

	if(Local_u8Counter == 1u)
	{
		ICU_SW_u8Reading1 = Timer1_u16GetTimerValue();
		EXTI_u8SetSenseCtrl(INT0,FALLING_EDGE);
	}
	else if(Local_u8Counter == 2u)
	{
		Local_u8Counter = 0;
		ICU_SW_u8Reading2 = Timer1_u16GetTimerValue();
		if(OVF_SW_u8Counter > 0)
		{
			ICU_SW_u8Reading2 += (TIMER1_OVF_TICKS * OVF_SW_u8Counter);
			OVF_SW_u8Counter = 0;
		}
		EXTI_u8DisableIntChannel(INT0);
		Timer_voidInterruptDisable(INT_T1_OVF);
	}
	else
	{
		//Do nothing
	}
}
