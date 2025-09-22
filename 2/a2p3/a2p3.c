/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
*/
/*
 * Modified by Wagner Morais on Aug 2023.
*/
#include <stdio.h>
#include <stdlib.h>
#include "expstruct.h"
#include "led.h"
#include "rpi-systimer.h"
#include "piface.h"

#define LINE 32

int main()
{
	
	char str[LINE];
	led_init();

	piface_init();
	RPI_WaitMicroSeconds(2000000);
	
    ExpStruct* value;

	// cyclic execution
    while (1) {
		value = iexp();

		if (value) {
			piface_clear();
			for (int i = 0; i < LINE; i++)
			{
				str[i] = '\0';
			}
			if (value->expFraction < 10)
			{
				sprintf(str,"%d: %d.0%d\n", value->x, value->expInt, value->expFraction);
			} else {
				sprintf(str,"%d: %d.%d\n", value->x, value->expInt, value->expFraction);
			}
			
			piface_puts(str);
			free(value);
			value = NULL;
		}

		led_toggle();	// or led_blink();
    }
	return 0;
}
