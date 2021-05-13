/*
 * multipexer2x4.h
 *
 * Created: 13/05/2021 11:59:01
 *  Author: sjno
 */ 

#ifndef MULTIPEXER2X4_H_
#define MULTIPEXER2X4_H_

#include <avr/io.h>

typedef enum
{
	BANK_ONE = 1 << PORTB0;
	BANK_TWO = 1 << PORTB1;
} BankNumber;

typedef enum
{
	LED_0 = 1 << PORTB2;
	LED_1 = 1 << PORTB3;
	LED_2 = 1 << PORTB4;
	LED_3 = 1 << PORTB5;
} LedNumber;

typedef enum
{
	MP_LED_0 = BANK_ONE | LED_0;
	MP_LED_1 = BANK_ONE | LED_1;
	MP_LED_2 = BANK_ONE | LED_2;
	MP_LED_3 = BANK_ONE | LED_3;
	MP_LED_4 = BANK_TWO | LED_0;
	MP_LED_5 = BANK_TWO | LED_1;
	MP_LED_6 = BANK_TWO | LED_2;
	MP_LED_7 = BANK_TWO | LED_3;
} MultiplexdLedNumber;

#endif /* MULTIPEXER2X4_H_ */