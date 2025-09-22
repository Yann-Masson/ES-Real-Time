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
#include "rpi-systimer.h"

struct PendingExpData
{
    int x;
    int n;
    double sum;
    double term;
    double factorial;
    double xpow;
};

static struct PendingExpData* pendingExp = NULL;

static int currentX = 1;

#define TASK_MAX_TIME 100000

ExpStruct *iexp() {
	// pre-condition
    // if (x < 0 || x > 20)
    // {
    //     fprintf(stderr, "Error: Invalid input range\n");
    //     exit(1);
    // }

    if (pendingExp == NULL) {
        pendingExp = malloc(sizeof(struct PendingExpData));

        if (pendingExp == NULL) {
            fprintf(stderr, "Error: can't malloc");
            exit(1);
        }

        pendingExp->factorial = 1;
        pendingExp->n = 1;
        pendingExp->sum = 1;
        pendingExp->term = 0;
        pendingExp->xpow = 1;
    }


    const rpi_sys_timer_t* rpiSystemTimer = RPI_GetSystemTimer();

    volatile uint32_t now = rpiSystemTimer->counter_lo;

    bool completed = false;
    
    while (pendingExp->n < 100 && (( rpiSystemTimer->counter_lo - now ) < TASK_MAX_TIME)) {

        pendingExp->factorial = pendingExp->factorial * pendingExp->n;
        pendingExp->xpow = pendingExp->xpow * currentX;
        pendingExp->term = pendingExp->xpow / pendingExp->factorial;

        pendingExp->sum = pendingExp->sum + pendingExp->term;

        if (pendingExp->term < 0.0001) {
            completed = true;
            break;
        }
        
        pendingExp->n += 1;

        RPI_WaitMicroSeconds(50000);
    }

    if (pendingExp->n == 100)
    {
        completed = true;
    }
    

    if (completed) {
        ExpStruct* e = malloc(sizeof(ExpStruct));

        // divide into integer and fraction part
        e->x = currentX;
        e->expInt = (int)pendingExp->sum;
        e->expFraction = (int)(((pendingExp->sum - e->expInt) * 100) + 0.5);

        // post-condition
        if (e->expFraction > 99)
        {
            fprintf(stderr, "Error: The fraction-part is over two digits\n");
            exit(1);
        }

        free(pendingExp);
        pendingExp = NULL;

        currentX += 1;

        if (currentX > 20) {
            currentX = 1;
        }

        return e;
    } else {
        return NULL;
    }
}
