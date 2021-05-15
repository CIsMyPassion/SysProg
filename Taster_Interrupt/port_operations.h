/*
 * port_operations.h
 *
 * Created: 15/05/2021 16:27:25
 *  Author: sjno
 */ 


#ifndef PORT_OPERATIONS_H_
#define PORT_OPERATIONS_H_

inline void set_bit_for_port(volatile uint8_t *port, uint8_t bit_number)
{
	*port |= (1 << bit_number);
}

inline void set_port(volatile uint8_t *port, uint8_t new_value)
{
	*port = new_value;
}

inline void clear_bit_for_port(volatile uint8_t *port, uint8_t bit_number)
{
	*port &= ~(1 << bit_number);
}

inline void clear_port(volatile uint8_t *port)
{
	*port = 0x00;
}

inline uint8_t read_bit_from_port(volatile uint8_t *port, uint8_t bit_number)
{
	return *port & (1 << bit_number);
}

inline uint8_t read_inverted_bit_from_port(volatile uint8_t *port, uint8_t bit_number)
{
	return (~(*port)) & (1 << bit_number);
}

inline void toggle_bit_for_port(volatile uint8_t *port, uint8_t bit_number)
{
	*port ^= (1 << bit_number);
}

inline void toggle_port(volatile uint8_t *port)
{
	*port ^= 0xff;
}

#endif /* PORT_OPERATIONS_H_ */