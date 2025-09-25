/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
 */
/*
 * Modified by Wagner Morais on Aug 2022.
 */
 
#ifndef _EXPSTRUCT_H
#define _EXPSTRUCT_H

struct expStruct {
    int x;
	int expInt;
	int expFraction;
};

typedef struct expStruct ExpStruct;

/** @brief approximate e^x using Taylor series expansion. 
 * 
 * @param x The exponent to which e is raised. Must be in the range 1 <= x <= 20.
 *
 *  @return A dynamically allocated pointer to an expStruct with the approximated value for e^x, 
 *          containing an integer part (expInt) and a fraction part with two digits (expFraction).
 *          Or NULL if the computation is not yet finished.
 *
 *  Pre-condition: 0 <= x <= 20
 *
 *  Post-condition: 0 <= e->expFraction <= 99, The fraction-part should only have two digits
 *  
 */
ExpStruct *iexp (int x);

#endif