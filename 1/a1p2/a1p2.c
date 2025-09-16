/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include <stdbool.h>

#include "led.h"

int main()
{
	led_init();

    while (true) {
        led_blink();
    }
}