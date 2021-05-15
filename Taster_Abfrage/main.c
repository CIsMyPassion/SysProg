/*
 * Taster_Abfrage.c
 *
 * Created: 12/05/2021 21:48:24
 * Author : sjno
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SET_BIT(BYTE, BIT) BYTE |= (1 << BIT)
#define CLEAR_BIT(BYTE, BIT) BYTE &= ~(1 << BIT)
#define TOGGLE_BIT(BYTE, BIT) BYTE ^= (1 << BIT)
#define TOGGLE_BYTE(BYTE) BYTE ^= 0xff;

#define READ_BIT(BYTE, BIT) BYTE & (1 << BIT)

#define LED PORTB5
#define OUTPUT PORTB

#define ON_BUTTON PORTD2
#define OFF_BUTTON PORTD3
#define INPUT_OPTION PORTD
#define INPUT PIND

void init()
{
	SET_BIT(DDRB, DDB5);
	
	CLEAR_BIT(DDRD, DDD2);
	CLEAR_BIT(DDRD, DDD3);
	
	CLEAR_BIT(OUTPUT, LED);
	
	SET_BIT(INPUT_OPTION, ON_BUTTON);
	SET_BIT(INPUT_OPTION, OFF_BUTTON);
}

int main(void)
{
	init();
	
	while (1)
	{
		if (READ_BIT(INPUT, ON_BUTTON))
		{
			SET_BIT(OUTPUT, LED);
		}
		
		if(READ_BIT(INPUT, OFF_BUTTON))
		{
			CLEAR_BIT(OUTPUT, LED);
		}
	}
}



