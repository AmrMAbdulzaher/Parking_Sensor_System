#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

typedef enum
{
	ECHO_PD2,
	ECHO_PD6
}ECHO_PINS_t;

typedef struct
{
	uint8 PORT;
	uint8 TRIG_PIN;
	uint8 ECHO_PIN;
}ULTRASONIC_CONFIG_t;

uint8 Ultrasonic_u8GetDistance(ULTRASONIC_CONFIG_t* Copy_pstConfiguration, uint16* Copy_pu16Distance_mm);

#endif /* ULTRASONIC_INTERFACE_H_ */
