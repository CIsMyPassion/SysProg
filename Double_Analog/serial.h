/*
 * serial.h
 *
 * Created: 17/05/2021 11:22:58
 *  Author: sjno
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

#include <avr/io.h>#include <avr/interrupt.h>#include <stdint.h>#include <stddef.h>
#define VAL F_CPU/16/100
typedef enum baudrate{	BAUD_300 = 300,	BAUD_600 = 600,	BAUD_1200 = 1200,	BAUD_2400 = 2400,	BAUD_4800 = 4800,	BAUD_9600 = 9600,	BAUD_14400 = 14400,	BAUD_19200 = 19200,	BAUD_28800 = 28800,	BAUD_31250 = 31250,	BAUD_38400 = 38400,	BAUD_57600 = 57600} Baudrate;inline uint16_t baudrate_value_for_register(Baudrate baudrate){	return VAL / (((uint16_t) 9600) / 100) - 1; // Calculate the ubrr value}typedef void (* Serial_Callback) (char);Serial_Callback callback_function;ISR (USART_RX_vect)
{
	if (callback_function != NULL) // Check if a callback is defined
	{
		callback_function(UDR0); // Execute the callback function
	}
}inline void serial_init(){	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);	callback_function = NULL;}inline void serial_interrupt_init(Serial_Callback callback){	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);	callback_function = callback;}inline void serial_set_baud_rate(Baudrate baudrate){	uint16_t value = baudrate_value_for_register(baudrate);	UBRR0H = (value >> 8); // Set the high 8 bit of the ubrr0 register	UBRR0L = value; // Set the low 8 bit of the ubrr0 register}inline void serial_send_char(uint8_t value){	while ( !(UCSR0A & (1 << UDRE0)) ) ; // Wait until a new character can be send	UDR0 = value; // Send the character}inline void serial_clear(){	serial_send_char(0x0c); // Send the clear control character}inline void serial_send_string(uint8_t *message){	while(*message) // Loop through the string and send every character		serial_send_char(*message ++);}inline void serial_send_string_new_line(uint8_t *message){	serial_send_string(message); // Send the actual message	serial_send_char('\r'); // Send the carriage return control character	serial_send_char('\n'); // Send the new line control character}

#endif /* SERIAL_H_ */