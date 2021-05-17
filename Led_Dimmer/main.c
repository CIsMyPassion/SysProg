/*
 * Led_Frequenzen.c
 *
 * Created: 12/05/2021 22:18:35
 * Author : sjno
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "port_operations.h"
#include "analog.h"

void set_pwm_handler(uint8_t adch)
{
	pwm_set_duty_cycle(adch);
}

void init()
{
	pwm_init();
	analog_init(&set_pwm_handler);
}

int main(void)
{
    init();
	
    while (1);
}

