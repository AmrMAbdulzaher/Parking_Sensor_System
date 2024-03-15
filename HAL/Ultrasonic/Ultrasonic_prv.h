#ifndef ULTRASONIC_PRV_H_
#define ULTRASONIC_PRV_H_

#define CLK_PRESCALER_64			64UL
#define DIVIDE_FACTOR				2000UL
#define SOUND_SPEED_mm_PER_ms		343UL

#define TIMER1_OVF_TICKS			65536ul 		/*16 bits timer max*/


static void ICU_voidHW(void);
static void Timer1_voidOverflow(void);
static void ICU_voidSW(void);
#endif /* ULTRASONIC_PRV_H_ */
