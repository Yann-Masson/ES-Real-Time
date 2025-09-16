/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
	Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "uart.h"
#include "iregister.h"

#define LINE 80
#define MAX_FUNCTION_NAME_WITH_PARAMETERS 50

void printNumber(unsigned int number)
{
	if (number == 0) {
		uart_puts("0");
		return;
	}
	if (number / 10) {
		printNumber(number / 10);
	}
	char c = number % 10 + '0';
	char buffer[2] = { c, '\0' };

	uart_puts(buffer);
}

void printResult(char *functionNameWithParameters, int result, iRegister *r)
{
	char *bitString = NULL;
	
	uart_puts(functionNameWithParameters);
	uart_puts(" returned ");
	printNumber(result);
	
	if (r != NULL) {
		bitString = reg2str(*r);
		uart_puts(" (");
		uart_puts(bitString);
		uart_puts(")");
	}
	uart_puts("\n");
}

int retrieveUserInputNumber()
{
	int i = 0;
	char str[LINE] = {0};

	while (true) {
		char c = uart_getc();
		
		if (i >= LINE - 1) {
			str[i] = '\0';
			break;
		}
		
		// If the user press enter we break the while loop and terminate str
		if (c == '\n') {
			str[i] = '\0';
			break;
		}
		if (c >= '0' && c <= '9') {
			char buffer[2] = {c , '\0'};

			uart_puts(buffer);
			str[i] = c;
			i++;
		}
	}

	return atoi(str);
}

int main()
{
	iRegister r;
	int inumber, inibble, ibit, ishift = 0;

	// Using the uart
	// First, initialize and clear the channel
	uart_init();
	uart_clear();

	uart_puts("Enter an integer number (32 bit): ");
	inumber = retrieveUserInputNumber();
	r.content = inumber;
	uart_puts("\n");

	uart_puts("Enter the bit position (0 <= bit <= 31): ");
	ibit = retrieveUserInputNumber();
	uart_puts("\n");

	uart_puts("Enter the nibble position (0 <= bit <= 7): ");
	inibble = retrieveUserInputNumber();
	uart_puts("\n");

	uart_puts("Enter the number of bits to shift (0 <= bit <= 31): ");
	ishift = retrieveUserInputNumber();
	uart_puts("\n");

	uart_puts("You entered number: ");
	printNumber(inumber);
	uart_puts(" ");
	uart_puts(reg2str(r));
	uart_puts("\n");

	uart_puts("Bit: ");
	printNumber(ibit);

	uart_puts(", Nibble: ");
	printNumber(inibble);

	uart_puts("\n");
	
	setAll(&r);
	printResult("setAll(&r)", r.content, &r);
	
	resetAll(&r);
	printResult("resetAll(&r)", r.content, &r);

	setBit(ibit, &r);
	printResult("setBit(ibit, &r)", r.content, &r);

	int getBitResult = getBit(ibit, &r);
	printResult("getBit(ibit, &r)", getBitResult, NULL);

	resetBit(ibit, &r);
	printResult("resetBit(ibit, &r)", r.content, &r);

	assignNibble(inibble, 0xA, &r);
	printResult("assignNibble(inibble, 0xA, &r)", r.content, &r);

	int getNibbleResult = getNibble(inibble, &r);
	printResult("getNibble(inibble, &r)", getNibbleResult, &r);

	shiftRight(ishift, &r);
	printResult("shiftRight(ishift, &r)", r.content, &r);

	assignNibble(inibble, 0x5, &r);
	printResult("assignNibble(inibble, 0x5, &r)", r.content, &r);

	shiftLeft(ishift, &r);
	printResult("shiftLeft(ishift, &r)", r.content, &r);
}
