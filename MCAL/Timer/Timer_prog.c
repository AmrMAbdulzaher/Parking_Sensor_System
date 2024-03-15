#include "../../Library/STD_TYPES.h"
#include "../../Library/ErrType.h"
#include "../../Library/BIT_MATH.h"

#include "Timer_cfg.h"
#include "Timer_interface.h"
#include "Timer_prv.h"
#include "Timer_reg.h"

static void(*Timer_pvCallBackNotificationFunc[8])(void)= {NULL};


/*General Functions*/
void Timer_voidInterruptEnable(TIMER_INT_SRC_t Copy_enuInterruptSource)
{
	switch(Copy_enuInterruptSource)
	{
	case INT_T0_OC: SET_BIT(TIMSK,OCIE0); break;
	case INT_T0_OVF: SET_BIT(TIMSK,TOIE0); break;
	case INT_T1_IC: SET_BIT(TIMSK,TICIE1); SET_BIT(TCCR1B,ICNC1); break;
	case INT_T1_OCA: SET_BIT(TIMSK,OCIE1A); break;
	case INT_T1_OCB: SET_BIT(TIMSK,OCIE1B); break;
	case INT_T1_OVF: SET_BIT(TIMSK,TOIE1); break;
	case INT_T2_OC: SET_BIT(TIMSK,OCIE2); break;
	case INT_T2_OVF: SET_BIT(TIMSK,TOIE2); break;
	}
}
void Timer_voidInterruptDisable(TIMER_INT_SRC_t Copy_enuInterruptSource)
{
	switch(Copy_enuInterruptSource)
	{
	case INT_T0_OC: 	CLR_BIT(TIMSK,OCIE0); break;
	case INT_T0_OVF: 	CLR_BIT(TIMSK,TOIE0); break;
	case INT_T1_IC: 	CLR_BIT(TIMSK,TICIE1); CLR_BIT(TCCR1B,ICNC1); break;
	case INT_T1_OCA:	CLR_BIT(TIMSK,OCIE1A); break;
	case INT_T1_OCB: 	CLR_BIT(TIMSK,OCIE1B); break;
	case INT_T1_OVF: 	CLR_BIT(TIMSK,TOIE1); break;
	case INT_T2_OC: 	CLR_BIT(TIMSK,OCIE2); break;
	case INT_T2_OVF: 	CLR_BIT(TIMSK,TOIE2); break;
	}
}

uint8 Timer_u8SetCallBackFunction(TIMER_INT_SRC_t Copy_enuInterruptSource, void(*CallBackFunc)(void))
{
	uint8 Local_u8ErrorState = OK;

	if(CallBackFunc != NULL)
	{
		Timer_pvCallBackNotificationFunc[Copy_enuInterruptSource] = CallBackFunc;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

/************************************	Timer0 functions	************************************/
uint8 Timer0_u8Init(Timer0_Config_t* Copy_pstTimerConfig)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_pstTimerConfig != NULL)
	{
		/*Set Waveform generation mode*/
		TCCR0 &= T0_2_WGM_MASK;
		TCCR0 |= Copy_pstTimerConfig->WGM;

		/*Set Output Compare Mode*/
		TCCR0 &= T0_2_OCM_MASK;
		TCCR0 |= Copy_pstTimerConfig->OC_Mode;

		/*Set Prescaler*/
		TCCR0 &= CLK_MASK;
		TCCR0 |= Copy_pstTimerConfig->CLK;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;

}
void Timer0_voidSetPreloadValue(uint8 Copy_u8PreloadValue)
{
	TCCR0 = Copy_u8PreloadValue;
}
void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompareMatchValue)
{
	OCR0 = Copy_u8CompareMatchValue;
}
uint8 Timer0_u8GetTimerValue(void)
{
	return TCCR0;
}
void Timer0_voidSetPrescaler(TIMER0_1_PRESCALER_t Copy_enuPrescaler)
{
	TCCR0 &= CLK_MASK;
	TCCR0 |= Copy_enuPrescaler;
}
void Timer0_voidSetWaveGenerationMode(TIMER_WGM_t Copy_enuWGM)
{
	TCCR0 &= T0_2_WGM_MASK;
	TCCR0 |= Copy_enuWGM;
}
void Timer0_voidSetOutputCompareMode(TIMER_OC_MODE_t Copy_enuOCM)
{
	TCCR0 &= T0_2_OCM_MASK;
	TCCR0 |= Copy_enuOCM;
}


/************************************	Timer1 functions	************************************/
uint8 Timer1_u8Init(Timer1_Config_t* Copy_pstTimerConfig)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_pstTimerConfig != NULL)
	{
		/*Set Waveform generation mode A*/
		TCCR1A &= T1_WGMA_MASK;
		TCCR1A |= (Copy_pstTimerConfig->WGM & T1_WGM_VALUE_MASK_A);

		TCCR1B &= T1_WGMB_MASK;
		TCCR1B |= (Copy_pstTimerConfig->WGM & T1_WGM_VALUE_MASK_B);

		/*Set OutputCompare Mode*/
		switch(Copy_pstTimerConfig->OC_Mode)
		{
		case OC_MODE_DISCONNECT: CLR_BIT(TCCR1A,COM1A1); CLR_BIT(TCCR1A,COM1B1); CLR_BIT(TCCR1A,COM1A0); CLR_BIT(TCCR1A,COM1B0); break;
		case OC_MODE_TOGGLE: CLR_BIT(TCCR1A,COM1A1); CLR_BIT(TCCR1A,COM1B1); SET_BIT(TCCR1A,COM1A0); SET_BIT(TCCR1A,COM1B0); break;
		case OC_MODE_CLR: SET_BIT(TCCR1A,COM1A1); SET_BIT(TCCR1A,COM1B1); CLR_BIT(TCCR1A,COM1A0); CLR_BIT(TCCR1A,COM1B0); break;
		case OC_MODE_SET: SET_BIT(TCCR1A,COM1A1); SET_BIT(TCCR1A,COM1B1); SET_BIT(TCCR1A,COM1A0); SET_BIT(TCCR1A,COM1B0); break;
		}

		/*Set prescaler*/
		TCCR1B &= CLK_MASK;
		TCCR1B |= Copy_pstTimerConfig->CLK;

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
void Timer1_voidSetPreloadValue(uint16 Copy_u16PreloadValue)
{
	TCNT1 = Copy_u16PreloadValue;
}
uint8 Timer1_u8SetCompareMatchValue(TIMER1_COMP_REG_t Copy_enuRegister, uint16 Copy_u16CompareMatchValue)
{
	uint8 Local_u8ErrorState = OK;
	switch(Copy_enuRegister)
	{
	case OCR1A_REG: OCR1A = Copy_u16CompareMatchValue; break;
	case OCR1B_REG: OCR1B = Copy_u16CompareMatchValue; break;
	default: Local_u8ErrorState = NOK; break;
	}

	return Local_u8ErrorState;
}

void Timer1_voidSetInputCaptureValue(uint16 Copy_u16InputCaptureValue)
{
	ICR1 = Copy_u16InputCaptureValue;
}

uint16 Timer1_u16GetTimerValue(void)
{
	return TCNT1;
}
void Timer1_voidSetPrescaler(TIMER0_1_PRESCALER_t Copy_enuPrescaler)
{
	TCCR1B &= CLK_MASK;
	TCCR1B |= Copy_enuPrescaler;
}
void Timer1_voidSetWaveGenerationMode(TIMER_WGM_t Copy_enuWGM)
{
	TCCR1A &= T1_WGMA_MASK;
	TCCR1A |= (Copy_enuWGM & T1_WGM_VALUE_MASK_A);

	TCCR1B &= T1_WGMB_MASK;
	TCCR1B |= (Copy_enuWGM & T1_WGM_VALUE_MASK_B);
}
void Timer1_voidSetOutputCompareMode(TIMER_OC_MODE_t Copy_enuOCM)
{
	switch(Copy_enuOCM)
	{
	case OC_MODE_DISCONNECT: CLR_BIT(TCCR1A,COM1A1); CLR_BIT(TCCR1A,COM1B1); CLR_BIT(TCCR1A,COM1A0); CLR_BIT(TCCR1A,COM1B0); break;
	case OC_MODE_TOGGLE: CLR_BIT(TCCR1A,COM1A1); CLR_BIT(TCCR1A,COM1B1); SET_BIT(TCCR1A,COM1A0); SET_BIT(TCCR1A,COM1B0); break;
	case OC_MODE_CLR: SET_BIT(TCCR1A,COM1A1); SET_BIT(TCCR1A,COM1B1); CLR_BIT(TCCR1A,COM1A0); CLR_BIT(TCCR1A,COM1B0); break;
	case OC_MODE_SET: SET_BIT(TCCR1A,COM1A1); SET_BIT(TCCR1A,COM1B1); SET_BIT(TCCR1A,COM1A0); SET_BIT(TCCR1A,COM1B0); break;
	}
}

/************************************	Input Capture Unit Functions	************************************/
void ICU_voidSetTriggerEvent(ICU_TRIGGER_t Copy_enuTriggerEvent)
{
	switch(Copy_enuTriggerEvent)
	{
	case ICU_RISING_EDGE: SET_BIT(TCCR1B,ICES1); break;
	case ICU_FALLING_EDGE: CLR_BIT(TCCR1B,ICES1); break;
	}
}

uint16 ICU_u16GetReading(void)
{
	return ICR1;
}

/************************************	Timer2 functions	************************************/
uint8 Timer2_u8Init(Timer2_Config_t* Copy_pstTimerConfig)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_pstTimerConfig != NULL)
	{
		/*Set Waveform generation mode*/
		TCCR2 &= T0_2_WGM_MASK;
		TCCR2 |= Copy_pstTimerConfig->WGM;

		/*Set Output Compare Mode*/
		TCCR2 &= T0_2_OCM_MASK;
		TCCR2 |= Copy_pstTimerConfig->OC_Mode;

		/*Set prescaler*/
		TCCR2 &= CLK_MASK;
		TCCR2 |= Copy_pstTimerConfig->CLK;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
void Timer2_voidSetPreloadValue(uint8 Copy_u8PreloadValue)
{
	TCNT2 = Copy_u8PreloadValue;
}
void Timer2_voidSetCompareMatchValue(uint8 Copy_u8CompareMatchValue)
{
	OCR2 = Copy_u8CompareMatchValue;
}
uint8 Timer2_u8GetTimerValue(void)
{
	return TCNT2;
}
void Timer2_voidSetPrescaler(TIMER2_PRESCALER_t Copy_enuPrescaler)
{
	TCCR2 &= CLK_MASK;
	TCCR2 |= Copy_enuPrescaler;
}
void Timer2_voidSetWaveGenerationMode(TIMER_WGM_t Copy_enuWGM)
{
	TCCR2 &= T0_2_WGM_MASK;
	TCCR2 |= Copy_enuWGM;
}
void Timer2_voidSetOutputCompareMode(TIMER_OC_MODE_t Copy_enuOCM)
{
	TCCR2 &= T0_2_OCM_MASK;
	TCCR2 |= Copy_enuOCM;
}


/******************************** ISRs *************************************/

/*TIMER0 Overflow Interrupt ISR*/
__attribute__((signal)) void __vector_11(void);
void __vector_11(void)
{
	if(Timer_pvCallBackNotificationFunc != NULL)
	{
		Timer_pvCallBackNotificationFunc[INT_T0_OVF]();
	}
}
/*TIMER0 Output Compare Interrupt ISR*/
__attribute__((signal)) void __vector_10(void);
void __vector_10(void)
{
	if(Timer_pvCallBackNotificationFunc != NULL)
	{
		Timer_pvCallBackNotificationFunc[INT_T0_OC]();
	}
}

/*TIMER1 Overflow Interrupt ISR*/
__attribute__((signal)) void __vector_9(void);
void __vector_9(void)
{
	if(Timer_pvCallBackNotificationFunc != NULL)
	{
		Timer_pvCallBackNotificationFunc[INT_T1_OVF]();
	}
}

/*TIMER1 Output Compare B Interrupt ISR*/
__attribute__((signal)) void __vector_8(void);
void __vector_8(void)
{
	if(Timer_pvCallBackNotificationFunc != NULL)
	{
		Timer_pvCallBackNotificationFunc[INT_T1_OCB]();
	}
}

/*TIMER1 Output Compare A Interrupt ISR*/
__attribute__((signal)) void __vector_7(void);
void __vector_7(void)
{
	if(Timer_pvCallBackNotificationFunc != NULL)
	{
		Timer_pvCallBackNotificationFunc[INT_T1_OCA]();
	}
}

/*TIMER1 Input Capture Interrupt ISR*/
__attribute__((signal)) void __vector_6(void);
void __vector_6(void)
{
	if(Timer_pvCallBackNotificationFunc != NULL)
	{
		Timer_pvCallBackNotificationFunc[INT_T1_IC]();
	}
}

/*TIMER2 Overflow Interrupt ISR*/
__attribute__((signal)) void __vector_5(void);
void __vector_5(void)
{
	if(Timer_pvCallBackNotificationFunc != NULL)
	{
		Timer_pvCallBackNotificationFunc[INT_T2_OVF]();
	}
}

/*TIMER2 output compare Interrupt ISR*/
__attribute__((signal)) void __vector_4(void);
void __vector_4(void)
{
	if(Timer_pvCallBackNotificationFunc != NULL)
	{
		Timer_pvCallBackNotificationFunc[INT_T2_OC]();
	}
}
