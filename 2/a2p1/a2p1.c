/*
	Modified by Wagner Morais on Sep 2023.
 */

#include <stdio.h>
#include <stdbool.h>
#include "piface.h"
#include "rpi-systimer.h"

int main()
{
	piface_init();

	while(true) {

		piface_clear();
		piface_puts("Short string");
		RPI_WaitMicroSeconds(500000);
		
		piface_clear();
		piface_puts("This is a long string");
		RPI_WaitMicroSeconds(500000);

		piface_clear();
		piface_puts("1st line\n2nd line");
		RPI_WaitMicroSeconds(500000);
	}
	
	return 0;
}