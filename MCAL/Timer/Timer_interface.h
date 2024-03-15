#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

typedef enum
{
	NO_CLK_SRC,
	NO_PRESCALER,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024,
	EXT_CLK_FALLING_EDGE,
	EXT_CLK_RISING_EDGE,
}TIMER0_1_PRESCALER_t;

typedef enum
{
	T2_NO_CLK,
	T2_NO_PRESCALER,
	T2_PRESCALER_8,
	T2_PRESCALER_32,
	T2_PRESCALER_64,
	T2_PRESCALER_128,
	T2_PRESCALER_256,
	T2_PRESCALER_1024
}TIMER2_PRESCALER_t;

typedef enum{
	OC_MODE_DISCONNECT = 0u,
	OC_MODE_TOGGLE = 16u, 	//0b00010000
	OC_MODE_CLR = 32u, 		//0b00100000
	OC_MODE_SET = 48u 		//0b00110000
}TIMER_OC_MODE_t;

typedef enum{
	INT_T0_OVF,
	INT_T0_OC,
	INT_T1_OVF,
	INT_T1_OCB,
	INT_T1_OCA,
	INT_T1_IC,
	INT_T2_OVF,
	INT_T2_OC
}TIMER_INT_SRC_t;

typedef enum{
	WGM_NORMAL=0u,
	WGM_T1_PWM_PHA_CORR_8=1u,
	WGM_T1_PWM_PHA_CORR_9=2u,
	WGM_T1_PWM_PHA_CORR_10=3u,
	WGM_CTC=8u, //0b00001000
	WGM_T1_FAST_PWM_8=9u,
	WGM_T1_FAST_PWM_9=10u,
	WGM_T1_FAST_PWM_10=11u,
	WGM_T1_PWM_PHA_FREQ_CORR_ICR1=16u,
	WGM_T1_PWM_PHA_FREQ_CORR_OCR1A=17u,
	WGM_T1_PWM_PHA_CORR_ICR1=18u,
	WGM_T1_PWM_PHA_CORR_OCR1A=19u,
	WGM_T1_CTC_ICR1=24u,
	WGM_T1_FAST_PWM_ICR1=26u,
	WGM_T1_FAST_PWM_OCR1A=27u,
	WGM_PHA_CORR = 64u, //0b01000000
	WGM_FAST_PWM = 72u 	//0b01001000
}TIMER_WGM_t;

typedef enum{
	OCR1A_REG,
	OCR1B_REG
}TIMER1_COMP_REG_t;

typedef struct
{
	TIMER_WGM_t WGM;
	TIMER0_1_PRESCALER_t CLK;
	TIMER_OC_MODE_t OC_Mode;
}Timer0_Config_t;

typedef struct
{
	TIMER_WGM_t WGM;
	TIMER0_1_PRESCALER_t CLK;
	TIMER_OC_MODE_t OC_Mode;
}Timer1_Config_t;

typedef struct
{
	TIMER_WGM_t WGM;
	TIMER2_PRESCALER_t CLK;
	TIMER_OC_MODE_t OC_Mode;
}Timer2_Config_t;

typedef enum
{
	ICU_RISING_EDGE,
	ICU_FALLING_EDGE
}ICU_TRIGGER_t;

/*General Functions*/
void Timer_voidInterruptEnable(TIMER_INT_SRC_t Copy_enuInterruptSource);
void Timer_voidInterruptDisable(TIMER_INT_SRC_t Copy_enuInterruptSource);
uint8 Timer_u8SetCallBackFunction(TIMER_INT_SRC_t Copy_enuInterruptSource, void(*CallBackFunc)(void));

/*Timer0 functions*/
uint8 Timer0_u8Init(Timer0_Config_t* Copy_pstTimerConfig);
void Timer0_voidSetPreloadValue(uint8 Copy_u8PreloadValue);
void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompareMatchValue);
uint8 Timer0_u8GetTimerValue(void);
void Timer0_voidSetPrescaler(TIMER0_1_PRESCALER_t Copy_enuPrescaler);
void Timer0_voidSetWaveGenerationMode(TIMER_WGM_t Copy_enuWGM);
void Timer0_voidSetOutputCompareMode(TIMER_OC_MODE_t Copy_enuOCM);

/*Timer1 functions*/
uint8 Timer1_u8Init(Timer1_Config_t* Copy_pstTimerConfig);
void Timer1_voidSetPreloadValue(uint16 Copy_u16PreloadValue);
uint8 Timer1_u8SetCompareMatchValue(TIMER1_COMP_REG_t Copy_enuRegister, uint16 Copy_u16CompareMatchValue);
void Timer1_voidSetInputCaptureValue(uint16 Copy_u16InputCaptureValue);
uint16 Timer1_u16GetTimerValue(void);
void Timer1_voidSetPrescaler(TIMER0_1_PRESCALER_t Copy_enuPrescaler);
void Timer1_voidSetWaveGenerationMode(TIMER_WGM_t Copy_enuWGM);
void Timer1_voidSetOutputCompareMode(TIMER_OC_MODE_t Copy_enuOCM);

/*Input Capture Unit Functions*/
void ICU_voidSetTriggerEvent(ICU_TRIGGER_t Copy_enuTriggerEvent);
uint16 ICU_u16GetReading(void);

/*Timer2 functions*/
uint8 Timer2_u8Init(Timer2_Config_t* Copy_pstTimerConfig);
void Timer2_voidSetPreloadValue(uint8 Copy_u8PreloadValue);
void Timer2_voidSetCompareMatchValue(uint8 Copy_u8CompareMatchValue);
uint8 Timer2_u8GetTimerValue(void);
void Timer2_voidSetPrescaler(TIMER2_PRESCALER_t Copy_enuPrescaler);
void Timer2_voidSetWaveGenerationMode(TIMER_WGM_t Copy_enuWGM);
void Timer2_voidSetOutputCompareMode(TIMER_OC_MODE_t Copy_enuOCM);

#endif /* TIMER_INTERFACE_H_ */
