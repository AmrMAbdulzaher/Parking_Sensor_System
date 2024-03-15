#include "../Library/STD_TYPES.h"
#include "util/delay.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/PORT/PORT_interface.h"

#include "../HAL/CLCD/CLCD_interface.h"
#include "../HAL/LED/LED_interface.h"
#include "../HAL/BUZZ/BUZZ_interface.h"
#include "../HAL/Ultrasonic/Ultrasonic_interface.h"


void main(void)
{
	PORT_voidInit();
	CLCD_voidInit();
	GIE_voidEnableGlobal();

	ULTRASONIC_CONFIG_t Local_stUltrasonic1 =
	{
			.PORT = DIO_u8PORTD,
			.TRIG_PIN = DIO_u8PIN7,
			.ECHO_PIN = ECHO_PD2,
	};

	ULTRASONIC_CONFIG_t Local_stUltrasonic2 =
	{
			.PORT = DIO_u8PORTD,
			.TRIG_PIN = DIO_u8PIN5,
			.ECHO_PIN = ECHO_PD6,
	};

	LED_Config_t Local_stRedLED=
	{
			.u8ACT_type = LED_ACT_HIGH,
			.u8Port = DIO_u8PORTC,
			.u8Pin = DIO_u8PIN0
	};

	LED_Config_t Local_stBlueLED=
	{
			.u8ACT_type = LED_ACT_HIGH,
			.u8Port = DIO_u8PORTC,
			.u8Pin = DIO_u8PIN2
	};

	LED_Config_t Local_stGreenLED=
	{
			.u8ACT_type = LED_ACT_HIGH,
			.u8Port = DIO_u8PORTC,
			.u8Pin = DIO_u8PIN1

	};

	BUZZ_Config_t Local_stBuzzer=
	{
			.u8ACT_type = BUZZ_ACT_HIGH,
			.u8Port = DIO_u8PORTC,
			.u8Pin = DIO_u8PIN5
	};
	uint16 Local_u16Distance1 = 0u;
	uint16 Local_u16Distance2 = 0u;
	while(1)
	{
		Ultrasonic_u8GetDistance(&Local_stUltrasonic1,&Local_u16Distance1);
		Ultrasonic_u8GetDistance(&Local_stUltrasonic2,&Local_u16Distance2);
		Local_u16Distance1 /= 10; /*from mm to cm*/
		Local_u16Distance2 /= 10; /*from mm to cm*/

		/*Get minimum distance*/
		uint16 Local_u16MinDistance = Local_u16Distance1 < Local_u16Distance2? Local_u16Distance1 : Local_u16Distance2;

		if(Local_u16MinDistance < 10)
		{
			/*Toggle Red LED and Buzzer*/
			LED_u8Toggle(&Local_stRedLED);
			BUZZ_u8Toggle(&Local_stBuzzer);

			/*Set Green and Blue LED off*/
			LED_u8SetOff(&Local_stBlueLED);
			LED_u8SetOff(&Local_stGreenLED);

			/*Show Message*/
			CLCD_voidGoToXY(0,0);
			CLCD_u8SendString(" DUDE! WATCHOUT ");
			CLCD_voidGoToXY(0,1);
			CLCD_u8SendString("DISTANCE < 10 cm");

			/*slower toggling*/
			_delay_ms(100);
		}
		else if((Local_u16MinDistance < 20) && (Local_u16MinDistance >= 10))
		{
			/*Toggle Red LED and Buzzer*/
			LED_u8Toggle(&Local_stGreenLED);
			BUZZ_u8Toggle(&Local_stBuzzer);

			/*Set Red and Blue LED off*/
			LED_u8SetOff(&Local_stBlueLED);
			LED_u8SetOff(&Local_stRedLED);

			/*Show Message*/
			CLCD_voidGoToXY(0,0);
			CLCD_u8SendString("  Be Careful !  ");
			CLCD_voidGoToXY(0,1);
			CLCD_u8SendString("DISTANCE < 20 cm");

			/*slower toggling*/
			_delay_ms(300);
		}
		else
		{
			/*Set Blue LED on*/
			LED_u8SetOn(&Local_stBlueLED);

			/*Set Red and Blue LED off*/
			LED_u8SetOff(&Local_stGreenLED);
			LED_u8SetOff(&Local_stRedLED);
			BUZZ_u8SetOff(&Local_stBuzzer);

			/*Show Message*/
			CLCD_voidGoToXY(0,0);
			CLCD_u8SendString("     CLEAR      ");
			CLCD_voidGoToXY(0,1);
			CLCD_u8SendString("DISTANCE > 20 cm");
		}

	}
}
