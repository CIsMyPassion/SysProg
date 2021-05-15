/*
 * ByteOperations.h
 *
 * Created: 15/05/2021 14:19:30
 *  Author: sjno
 */ 


#ifndef BYTE_OPERATIONS_H_
#define BYTE_OPERATIONS_H_

#include <stdint.h>

inline uint8_t get_bitshifted_by(uint8_t bitshift)
{
	return 1 << bitshift;
}

#endif /* BYTEOPERATIONS_H_ */