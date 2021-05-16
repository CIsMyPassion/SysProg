/*
 * timer_operations.h
 *
 * Created: 16.05.2021 12:07:58
 *  Author: Jannis Kruse
 */ 

#ifndef TIMER_OPERATIONS_H_
#define TIMER_OPERATIONS_H_

inline uint8_t calc_ocrn(uint8_t frequency, uint8_t prescaler_value)
{
	uint8_t ocrn = (((16000000 / prescaler_value) * (1 / frequency)) - 1);
	return ocrn;
}

#endif /* TIMER_OPERATIONS_H_ */