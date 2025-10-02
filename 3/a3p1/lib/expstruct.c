/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
 */
/*
 * Modified by Wagner Morais on Aug 2022.
 */
 
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "expstruct.h"
#include <stdio.h>
#include "led.h"
#include "rpi-systimer.h"

#define MAX_ITERATIONS 100

static int loop_counter = 0;

ExpStruct *iexp(int x) {
	// pre-condition
    if (x < 0 || x > 20){
        fprintf(stderr, "Error: Invalid input range\n");
        return NULL;
    }

    int n = 1;
    double sum = 1; //the sum of the taylor-expansion, where 1 is the first term for n = 0
    double term;
    double factorial = 1;
    double xpow = 1;

    while (n < 100) {

        factorial = factorial * n;
        xpow = xpow * x;
        term = xpow / factorial;

        sum = sum + term;

        // control if the term is so small that it does not affect the sum, if so then break the while loop
        if (term < 0.0001) break;

        n++;
        loop_counter++;

        if (loop_counter >= MAX_ITERATIONS) {
            loop_counter = 0;
            led_toggle();
        }

        // a delay to make the results visually observable
        // RPI_WaitMicroSeconds(10000);
    }

    ExpStruct* e = malloc(sizeof(ExpStruct));
    if (e == NULL){
        fprintf(stderr, "Error: Failed memory allocation\n");
        return NULL;
    }

    // divide the sum into integer and fraction part
    e->expInt = (int)sum;
    e->expFraction = (int)(((sum - e->expInt) * 100) + 0.5);

    // post-condition
    if (e->expFraction > 99 || e->expFraction <0){
        fprintf(stderr, "Error: The fraction-part is not two digits\n");
        free(e);
        return NULL;
    }

    return e;
}
