// ============================================================
// IRegister - Implementation of an Integer Register
// ============================================================

#include <stdlib.h>
#include <stdio.h>
#include "iregister.h"

void resetAll(iRegister* r) {
	// pre-condition
	if (r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to resetAll\n");
		exit(1);
	}

	r->content = 0;

	// post-condition
	if (r->content != 0)
	{
		fprintf(stderr, "Error: Failed to reset all Bits\n");
		exit(1);
	}
}


void setBit(int i, iRegister *r) {
	// pre-condition
	if (r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to setBit\n");
		exit(1);
	}
	// pre-condition
	if (i < 0 || i > 31)
	{
		fprintf(stderr, "Error: Invalid bit\n");
		exit(1);
	}

	r->content |= (1 << i);

	// post-condition
	if ((r->content & (1 << i)) == 0)
	{
		fprintf(stderr, "Error: Failed to set Bit\n");
		exit(1);
	}
}


void setAll(iRegister *r) {
	// pre-condition
	if (r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to setAll\n");
		exit(1);
	}

	r->content = ~0; //inverts all the 32 bits of 0s to 1s. 

	// post-condition
	if (r->content != ~0)
	{
		fprintf(stderr, "Error: Failed to set all Bits\n");
		exit(1);
	}
}


int getBit(int i, iRegister *r) {
	// pre-condition
	if (r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to getBit\n");
		exit(1);
	}
	// pre-condition
	if (i < 0 || i > 31)
	{
		fprintf(stderr, "Error: Invalid bit\n");
		exit(1);
	}

	/*
	* does an "AND" operation that resets all the bits to 0 except for bit i. 
	* If the calculated value is not equal to 0 then the i'th bit is set -> so we return 1. 
	*/
	if ((r->content & (1 << i)) != 0) return 1;

	return 0;
}

void assignNibble(int pos, int value, iRegister *r) {
    // pre-condition
    if (r == NULL) {
        fprintf(stderr, "Error: A NULL pointer was given to assignNibble\n");
        exit(1);
    }
    if (pos < 0 || pos > 7) {
        fprintf(stderr, "Error: Invalid position\n");
        exit(1);
    }
    if (value < 0 || value > 15) {
        fprintf(stderr, "Error: Invalid value\n");
        exit(1);
    }

    r->content &= ~(0xF << (4 * pos)); // Clear the nibble
    r->content |= ((value & 0xF) << (4 * pos)); // Set the nibble to value

    // post-condition
    if (getNibble(pos, r) != value) {
        fprintf(stderr, "Error: Failed to assign Nibble, got %d, expected %d\n", getNibble(pos, r), value);
        exit(1);
    }
}

int getNibble(int pos, iRegister *r) {
    // pre-condition
    if (r == NULL) {
        fprintf(stderr, "Error: A NULL pointer was given to getNibble\n");
        exit(1);
    }
    if (pos < 0 || pos > 7) {
        fprintf(stderr, "Error: Invalid position\n");
        exit(1);
    }

    return (r->content >> (4 * pos)) & 0xF;
}

char *reg2str(iRegister r) {
    static char bitString[33];

    for (int i = 31; i >= 0; i--) {
        if (r.content & (1 << i)) {
            bitString[31 - i] = '1';
        } else {
            bitString[31 - i] = '0';
        }
    }
    bitString[32] = '\0';

    return bitString;
}

void shiftRight(int n, iRegister *r) {
    // pre-condition
    if (r == NULL) {
        fprintf(stderr, "Error: A NULL pointer was given to shiftRight\n");
        exit(1);
    }
    if (n < 1 || n > 32) {
        fprintf(stderr, "Error: Invalid shift amount\n");
        exit(1);
    }

    r->content >>= n;

    // post-condition
    for (int i = 31; i >= 32 - n; i--) {
        if ((r->content & (1 << i)) != 0) {
            fprintf(stderr, "Error: Failed to shift right, bit %d is not zero\n", i);
            exit(1);
        }
    }
}

void shiftLeft(int n, iRegister *r) {
    // pre-condition
    if (r == NULL) {
        fprintf(stderr, "Error: A NULL pointer was given to shiftLeft\n");
        exit(1);
    }
    if (n < 1 || n > 32) {
        fprintf(stderr, "Error: Invalid shift amount\n");
        exit(1);
    }

    r->content <<= n;

    // post-condition
    for (int i = 0; i < n; i++) {
        if ((r->content & (1 << i)) != 0) {
            fprintf(stderr, "Error: Failed to shift left, bit %d is not zero\n", i);
            exit(1);
        }
    }
}

void resetBit(int i, iRegister *r) {
    // pre-condition
    if (r == NULL) {
        fprintf(stderr, "Error: A NULL pointer was given to resetBit\n");
        exit(1);
    }
    // pre-condition
    if (i < 0 || i > 31) {
        fprintf(stderr, "Error: Invalid bit\n");
        exit(1);
    }

    r->content &= ~(1 << i);

    // post-condition
    if ((r->content & (1 << i)) != 0) {
        fprintf(stderr, "Error: Failed to reset Bit\n");
        exit(1);
    }
}
