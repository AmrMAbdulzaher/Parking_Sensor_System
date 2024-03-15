#ifndef TIMER_REG_H_
#define TIMER_REG_H_

#define TCCR0					*((volatile uint8*)0x53)		/*Timer/Counter 0 control register*/
#define TCNT0					*((volatile uint8*)0x52)		/*Timer/Counter 0 register*/
#define OCR0					*((volatile uint8*)0x5C)		/*Output Compare 0 register*/

#define TCCR1A					*((volatile uint8*)0x4F)		/*Timer/Counter 1 control register A*/
#define COM1A1					7u
#define COM1A0					6u
#define COM1B1					5u
#define COM1B0					4u
#define TCCR1B					*((volatile uint8*)0x4E)		/*Timer/Counter 1 control register B*/
#define ICNC1					7u
#define ICES1					6u
#define TCNT1					*((volatile uint16*)0x4C)		/*Timer/Counter 1 register*/
#define OCR1A					*((volatile uint16*)0x4A)		/*Output Compare 1 register A*/
#define OCR1B					*((volatile uint16*)0x48)		/*Output Compare 1 register B*/
#define ICR1					*((volatile uint16*)0x46)		/*Input capture 1 register*/

#define TCCR2					*((volatile uint8*)0x45)		/*Timer/Counter 2 control register*/
#define TCNT2					*((volatile uint8*)0x44)		/*Timer/Counter 2 register*/
#define OCR2					*((volatile uint8*)0x43)		/*Output Compare 2 register*/

#define TIMSK					*((volatile uint8*)0x59)		/*Timer/Counter interrupt mask register*/
#define OCIE2					7u
#define TOIE2					6u
#define TICIE1					5u
#define OCIE1A					4u
#define OCIE1B					3u
#define TOIE1					2u
#define OCIE0					1u
#define TOIE0					0u

#endif /* TIMER_REG_H_ */
