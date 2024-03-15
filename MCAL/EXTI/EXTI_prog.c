#include "../../Library/STD_TYPES.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/ErrType.h"

#include "EXTI_prv.h"
#include "EXTI_interface.h"
#include "EXTI_cfg.h"
#include "EXTI_reg.h"


static void(*EXIT_pvCallBack[3])(void)={NULL};

void EXTI_voidInit(void)
{
#if INT0_SENSE_CTRL == EXTI_LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SESE_CTRL == EXTI_ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	LR_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE_CTRL == EXTI_FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE_CTRL == EXTI_RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#else
#error Wrong INT0_SENSE_CTRL configuration option
#endif

#if INT1_SENSE_CTRL == EXTI_LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SESE_CTRL == EXTI_ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE_CTRL == EXTI_FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE_CTRL == EXTI_RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#else
#error Wrong INT1_SENSE_CTRL configuration option
#endif


#if INT2_SENSE_CTRL == EXTI_FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);
#elif INT2_SENSE_CTRL == EXTI_RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);
#else
#error Wrong INT2_SENSE_CTRL configuration option
#endif


#if INT0_INIT_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);
#elif INT0_INIT_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);
#else
#error Wrong INT0_INIT_STATE configuration option
#endif

#if INT1_INIT_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);
#elif INT1_INIT_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);
#else
#error Wrong INT1_INIT_STATE configuration option
#endif

#if INT2_INIT_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);
#elif INT2_INIT_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);
#else
#error Wrong INT2_INIT_STATE configuration option
#endif

}

uint8 EXTI_u8SetSenseCtrl(IntChannel_t Copy_IntChannel, SenseCtrl_t Copy_SenseCtrl)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_IntChannel == INT0)
	{
		switch(Copy_SenseCtrl)
		{
		case LOW_LEVEL: CLR_BIT(MCUCR,MCUCR_ISC00); CLR_BIT(MCUCR,MCUCR_ISC01); break;
		case ON_CHANGE: SET_BIT(MCUCR,MCUCR_ISC00); CLR_BIT(MCUCR,MCUCR_ISC01); break;
		case FALLING_EDGE: CLR_BIT(MCUCR,MCUCR_ISC00); SET_BIT(MCUCR,MCUCR_ISC01); break;
		case RISING_EDGE: SET_BIT(MCUCR,MCUCR_ISC00); SET_BIT(MCUCR,MCUCR_ISC01); break;
		default: Local_u8ErrorState = NOK;	break;
		}
	}
	else if(Copy_IntChannel == INT1)
	{
		switch(Copy_SenseCtrl)
		{
		case LOW_LEVEL: CLR_BIT(MCUCR,MCUCR_ISC10); CLR_BIT(MCUCR,MCUCR_ISC11); break;
		case ON_CHANGE: SET_BIT(MCUCR,MCUCR_ISC10); CLR_BIT(MCUCR,MCUCR_ISC11); break;
		case FALLING_EDGE: CLR_BIT(MCUCR,MCUCR_ISC10); SET_BIT(MCUCR,MCUCR_ISC11); break;
		case RISING_EDGE: SET_BIT(MCUCR,MCUCR_ISC10); SET_BIT(MCUCR,MCUCR_ISC11); break;
		default: Local_u8ErrorState = NOK;	break;
		}
	}
	else if(Copy_IntChannel == INT2)
	{
		switch(Copy_SenseCtrl)
		{
		case FALLING_EDGE: CLR_BIT(MCUCSR,MCUCSR_ISC2); SET_BIT(MCUCSR,MCUCSR_ISC2); break;
		case RISING_EDGE: SET_BIT(MCUCSR,MCUCSR_ISC2); SET_BIT(MCUCSR,MCUCSR_ISC2); break;
		default: Local_u8ErrorState = NOK;	break;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

uint8 EXTI_u8EnableIntChannel(IntChannel_t Copy_IntChannel)
{
	uint8 Local_u8ErrorState = OK;

	switch(Copy_IntChannel)
	{
	case INT0: SET_BIT(GICR,GICR_INT0); break;
	case INT1: SET_BIT(GICR,GICR_INT1); break;
	case INT2: SET_BIT(GICR,GICR_INT2); break;
	default: Local_u8ErrorState = NOK;	break;
	}

	return Local_u8ErrorState;
}


uint8 EXTI_u8DisableIntChannel(IntChannel_t Copy_IntChannel)
{
	uint8 Local_u8ErrorState = OK;

	switch(Copy_IntChannel)
	{
	case INT0: CLR_BIT(GICR,GICR_INT0); break;
	case INT1: CLR_BIT(GICR,GICR_INT1); break;
	case INT2: CLR_BIT(GICR,GICR_INT2); break;
	default: Local_u8ErrorState = NOK; break;
	}

	return Local_u8ErrorState;
}

uint8 EXIT_u8SetCallBack(IntChannel_t Copy_IntChannel,void(*Copy_pvCallBackFun)(void))
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_pvCallBackFun != NULL)
	{
		if((Copy_IntChannel == INT0) | (Copy_IntChannel == INT1) | (Copy_IntChannel == INT2))
		{
			EXIT_pvCallBack[Copy_IntChannel] = Copy_pvCallBackFun;
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/*INT0 ISR*/
__attribute__((signal)) void __vector_1 (void);
void __vector_1 (void)
{
	if(EXIT_pvCallBack[INT0] != NULL)
	{
		EXIT_pvCallBack[INT0]();
	}
}

/*INT1 ISR*/
__attribute__((signal)) void __vector_2 (void);

void __vector_2 (void)
{
	if(EXIT_pvCallBack[INT1] != NULL)
	{
		EXIT_pvCallBack[INT1]();
	}
}

/*INT2 ISR*/
__attribute__((signal)) void __vector_3 (void);
void __vector_3 (void)
{
	if(EXIT_pvCallBack[INT2] != NULL)
	{
		EXIT_pvCallBack[INT2]();
	}
}

