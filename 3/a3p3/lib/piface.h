/*
    Part of the Real-Time Embedded Systems course at Halmstad University
*/

#ifndef _PIFACE_H
#define _PIFACE_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

/* PiFace Hardware Description */

/* MCP23S17 Control Register */
#define MCP_IODIRA 0x00
#define MCP_IODIRB 0x01
#define MCP_IPOLA 0x02
#define MCP_IPOLB 0x03
#define MCP_GPINTENA 0x04
#define MCP_GPINTENB 0x05
#define MCP_DEFVALA 0x06
#define MCP_DEFVALB 0x07
#define MCP_INTCONA 0x08
#define MCP_INTCONB 0x09
#define MCP_IOCON 0x0A
#define MCP_IOCON_ 0x0B
#define MCP_GPPUA 0x0C
#define MCP_GPPUB 0x0D
#define MCP_INTFA 0x0E
#define MCP_INTFB 0x0F
#define MCP_INTCAPA 0x10
#define MCP_INTCAPB 0x11
#define MCP_GPIOA 0x12
#define MCP_GPIOB 0x13
#define MCP_OLATA 0x14
#define MCP_OLATB 0x15

/* HD44780 Control Pins */
#define LCD_DB4 (1 << 0)
#define LCD_DB5 (1 << 1)
#define LCD_DB6 (1 << 2)
#define LCD_DB7 (1 << 3)
#define LCD_EN (1 << 4)
#define LCD_RW (1 << 5)
#define LCD_RS (1 << 6)
#define LCD_BL (1 << 7)

#define LCD_DELAY                                              \
    do                                                         \
    {                                                          \
        for (volatile int DELAYx = 0; DELAYx < 5000; DELAYx++) \
            ;                                                  \
    } while (0);

#define PUTTOLDC(fmt, args...)   \
    {                            \
        char s[9];               \
        sprintf(s, fmt, ##args); \
        piface_puts(s);          \
    }

static const uint8_t ROW_OFFSETS[] = {0, 0x40};

void piface_init(void);
void piface_putc(char c);
void piface_puts(char s[]);
void piface_clear();

/**
 *  @brief Sets the cursor on a specific row and column
 *  Please check the url: http://piface.github.io/libpifacedigital/
 *
 *  @param uint8_t col indicates the columns to position the cursor
 *  @param uint8_t row indicates row 0 (first) or 1 (second)
 */
void piface_set_cursor(uint8_t col, uint8_t row);

/**
 *  @brief Displays an integer content in a given segment in the PiFace display.
 *  Suppose that you decided to segment the display into 4 segments of 8 digits each.
 *  For example, the illustration below ...
 *      ------------------
 *      |S0:XXXXXS1:XXXXX|
 *      |S2:XXXXXS3:XXXXX|
 *      ------------------
 *  shows each segment (seg:0...3) with digits each.
 *  @param int seg Is the segment, i.e., 0: top left, 1:top right, 2: bottom left and 3: bottom right.
 *  @param int num Is the integer input parameter to be displayed.
 *
 *  NOTE: maybe, you want to display arbitrary content on a given segment. For example:
 *      printAtSeg(1, "S%i: %.1f", 1, 3.14);
 *  This requires the use of variadic arguments with proper string formatting.
 *  Please check the url: https://en.cppreference.com/w/c/language/variadic
 *  You can redeclare printAtSeg as:
 *     void printAtSeg(int seg, const char* fmt, ...);
 */
void print_at_seg(int seg, int num);

/**
 * @brief Sets the cursor at the beginning of a given segment.
 *
 * Pre-condition: 0<=seg<=3
 */
void piface_set_cursor_at_seg(int seg);

/**
 * @brief Clears a given segment by writing 8 spaces at the beginning of the segment.
 *
 * Pre-condition: 0<=seg<=3
 */
void piface_clear_seg(int seg);

/** 
 * @brief Similar to print_at_seg, but displays arbitrary content on a given segment. For example:
 *      printAtSeg(1, "S%i: %.1f", 1, 3.14);
 *  This requires the use of variadic arguments with proper string formatting.
 *  Please check the url: https://en.cppreference.com/w/c/language/variadic
 *  You can redeclare printAtSeg as:
 *     void printAtSeg(int seg, const char* fmt, ...);
 */
void printf_at_seg(int seg, const char *fmt, ...);

#endif
