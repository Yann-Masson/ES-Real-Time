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

/** @brief approximate e^x using Taylor series expansion. 
 *
 *  @param x the exponent of the fuction e^x
 *
 *  @return the approximated value of e^x in structure expStruct, 
 *  consisting of an integer part and a fraction part (2 digits)
 *
 *  Pre-condition: 0 <= x <= 20
 *
 *  Post-condition: e->expFraction < 100, The fraction-part should only have two digits
 *
 *  properties:
 *  
 */
ExpStruct *iexp (int);

#endif