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
	int expInt;
	int expFraction;
};

typedef struct expStruct ExpStruct;

/** @brief Approximate e^x using Taylor series expansion. 
 *
 *  @param x the exponent of the fuction e^x
 *
 *  @return A dynamically allocated pointer to an expStruct with the approximated value for e^x, 
 *          containing an integer part (expInt) and a fraction part with two digits (expFraction)
 *
 *  Pre-condition: 0 <= x <= 20
 *
 *  Post-condition: 0 <= expFraction <= 99, The fraction-part should only have two digits
 *  
 */
ExpStruct *iexp (int);

#endif
