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
#include "expstruct.h"
#include <stdio.h>
#include "rpi-systimer.h"

ExpStruct *iexp(int x){
	// pre-condition
    if (x < 0 || x > 20)
    {
        fprintf(stderr, "Error: Invalid input range\n");
        exit(1);
    }

    int n = 1;
    double sum = 1; //the sum of the taylor-expansion
    double term;
    double factorial = 1;
    double xpow = 1;

    while (n < 100) {

        factorial = factorial * n;
        xpow = xpow * x;
        term = xpow / factorial;

        sum = sum + term;

        // control if the term is so small that it does not affect the sum, if so then break...
        if (term < 0.0001) break;
        
        n++;

        RPI_WaitMicroSeconds(10000);
    }

    ExpStruct* e = malloc(sizeof(ExpStruct));

    // divide into integer and fraction part
    e->expInt = (int)sum;
    e->expFraction = (int)(((sum - e->expInt) * 100) + 0.5);


    // post-condition
    if (e->expFraction > 99)
    {
        fprintf(stderr, "Error: The fraction-part is over two digits\n");
        exit(1);
    }

    return e;
}
