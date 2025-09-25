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
	piface_init();
	piface_clear();

	led_init();
	
	piface_puts("DT8025 - A2P3");
	RPI_WaitMicroSeconds(2000000);
	
	while (1) {
		for (int i = 1; i <= 20; i++) {
			ExpStruct *value = iexp(i);
			
			piface_clear();

			if (value == NULL) {
				sprintf(str, "%d: An error occurred", i);
				piface_puts(str);
				continue;
			}

			if (value->expFraction < 10) {
				sprintf(str,"%d: %d.0%d\n", i, value->expInt, value->expFraction);
			} else {
				sprintf(str,"%d: %d.%d\n", i, value->expInt, value->expFraction);
			}
			piface_puts(str);
			free(value);
		}
	}

	return 0;
}
