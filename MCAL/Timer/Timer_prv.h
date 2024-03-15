#ifndef TIMER_PRV_H_
#define TIMER_PRV_H_

#define CLK_MASK				0b11111000

#define T0_2_WGM_MASK			0b10110111
#define T0_2_OCM_MASK			0b11001111

#define T1_WGMA_MASK			0b11111100
#define T1_WGM_VALUE_MASK_A		0b00000011

#define T1_WGMB_MASK			0b11100111
#define T1_WGM_VALUE_MASK_B		0b00011000

#define T1_OCMA_MASK			0b00111111
#define T1_OCMB_MASK			0b11001111

#define T0_TIMSK_BITS_MASK		0b11111100
#define T1_TIMSK_BITS_MASK		0b11000011
#define T2_TIMSK_BITS_MASK		0b00111111



#define NORMAL_WGM				1u
#define	CTC_WGM          		2u
#define FAST_PWN_WGM     		3u
#define PHASE_CORRECT_WGM		4u

#define IDLE					0u
#define BUSY					1u

#endif /* TIMER_PRV_H_ */
