/*
 * serial.h
 *
 * Created: 17/05/2021 11:22:58
 *  Author: sjno
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

#include <avr/io.h>
#define VAL F_CPU/16/100

{
	if (callback_function != NULL) // Check if a callback is defined
	{
		callback_function(UDR0); // Execute the callback function
	}
}
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

#endif /* SERIAL_H_ */