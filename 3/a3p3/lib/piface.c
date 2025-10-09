/*
	Part of the Real-Time Embedded Systems course at Halmstad University
	All rights reserved.
*/

/* PiFace Control and Display Driver */
#include <stdint.h>
#include <string.h>
#include "rpi-gpio.h"
#include "piface.h"

int cnt;

/* Bit-Banging SPI Driver */
static void spi_init(void)
{
	RPI_GetGpio()->GPFSEL0 |= (1 << 21);		   // GPIO  7,  9
	RPI_GetGpio()->GPFSEL1 |= (1 << 0) | (1 << 3); // GPIO 10, 11
	RPI_GetGpio()->GPSET0 = (1 << 7);			   // CE high
	RPI_GetGpio()->GPCLR0 = (1 << 11);			   // CLK low
}

static void spi_start(void)
{
	/* /CE low  */
	RPI_GetGpio()->GPCLR0 = (1 << 7);
}

static void spi_stop(void)
{
	/* /CE high */
	RPI_GetGpio()->GPSET0 = (1 << 7);
}

static void spi_byte(const uint8_t out, uint8_t *in)
{
	uint8_t tmpin = 0, tmpout = out;

	/* clock each bit out and read back */
	for (int i = 0; i < 8; i++)
	{
		tmpin <<= 1;

		if (tmpout & 0x80)
			RPI_GetGpio()->GPSET0 = (1 << 10); // set MOSI
		else
			RPI_GetGpio()->GPCLR0 = (1 << 10);

		if (RPI_GetGpio()->GPLEV0 & (1 << 9))
			tmpin |= 1; // read MISO

		RPI_GetGpio()->GPSET0 = (1 << 11); // set CLK
		RPI_GetGpio()->GPCLR0 = (1 << 11); // clear CLK

		tmpout <<= 1;
	}

	*in = tmpin;
	return;
}

static uint8_t mcp_read(const uint8_t reg)
{
	uint8_t in;

	spi_start();
	spi_byte(0x41, &in);
	spi_byte(reg, &in);
	spi_byte(0x00, &in);
	spi_stop();

	return in;
}

static void mcp_write(const uint8_t reg, const uint8_t val)
{
	uint8_t in;

	spi_start();
	spi_byte(0x40, &in);
	spi_byte(reg, &in);
	spi_byte(val, &in);
	spi_stop();
}

static void mcp_init(void)
{
	/* Port A: (S1 .. S5, S, L, R) */
	mcp_write(MCP_IODIRA, 0xFF);
	mcp_write(MCP_GPPUA, 0xFF);
	/* Port B: (DB4 .. DB7, /EN, R/W, RS, LED) */
	mcp_write(MCP_IODIRB, 0x00);
}

static uint8_t lcd_read_busy_flag_register()
{
	// Set read pin
	mcp_write(MCP_GPIOB, LCD_RW);

	// Set enable pin, keeping read pin high
	mcp_write(MCP_GPIOB, LCD_RW | LCD_EN);

	// Read bit 7 to 4
	uint8_t firstNibble = (mcp_read(MCP_GPIOB) & 0x0F);

	// Reset enable pin, keeping read pin high
	mcp_write(MCP_GPIOB, LCD_RW);

	// Set enable pin, keeping read pin high
	mcp_write(MCP_GPIOB, LCD_RW | LCD_EN);

	// Read bit 3 to 0
	uint8_t secondNibble = (mcp_read(MCP_GPIOB) & 0x0F);

	return ((firstNibble << 4) | secondNibble);
}

static void lcd_busy_wait()
{
	while (lcd_read_busy_flag_register() & 0x80)
		;
}

static void lcd_pulse(uint8_t val)
{
	mcp_write(MCP_GPIOB, val | LCD_EN);
	mcp_write(MCP_GPIOB, val);
}

static void lcd_write_cmd(uint8_t cmd)
{
	// lcd_busy_wait();
	/* write high nibble */
	lcd_pulse(LCD_BL | (cmd >> 4));
	lcd_busy_wait();
	/* write low nibble */
	lcd_pulse(LCD_BL | (cmd & 0x0F));
	LCD_DELAY;
}

static void lcd_write_data(uint8_t data)
{
	lcd_busy_wait();
	/* write high nibble */
	lcd_pulse(LCD_BL | LCD_RS | (data >> 4));
	lcd_busy_wait();
	/* write low nibble */
	lcd_pulse(LCD_BL | LCD_RS | (data & 0x0F));
}

static void lcd_init(void)
{
	/* enable 4 bit mode */
	LCD_DELAY;
	lcd_pulse(0x03);
	LCD_DELAY;
	lcd_pulse(0x03);
	LCD_DELAY;
	lcd_pulse(0x03);
	LCD_DELAY;
	lcd_pulse(0x02);
	LCD_DELAY;

	/* function set; N = 1 for two rows, F = 0 for 5x8 display */
	lcd_write_cmd(0x28);
	/* display clear */
	lcd_write_cmd(0x01);
	LCD_DELAY;

	/* entry mode set; I/D = 1 for direction left to right, S = 0 for shift off */
	lcd_write_cmd(0x06);
	/* display on/off; D = 1 for display on, C = 1 for cursor on; B = 0 for blinking off*/
	lcd_write_cmd(0x0E);
	// lcd_write_cmd( 0x0F );
}

__attribute__((constructor)) void piface_init(void)
{
	spi_init();
	mcp_init();
	lcd_init();
	cnt = 0;
}

uint8_t piface_getc(void)
{
	return mcp_read(MCP_GPIOA);
}

/** @brief Writes a character
 */
void piface_putc(char c)
{
	/* write character */
	if (cnt % 32 == 16)
	{
		lcd_write_cmd((0x40 | 0x80));
	}
	else
	{
		if (cnt % 32 == 0)
		{
			lcd_write_cmd(0x02);
			LCD_DELAY;
			cnt = 0;
		}
		else
		{
			if (c == '\n')
			{
				if (cnt > 16)
				{
					lcd_write_cmd(0x02);
					LCD_DELAY;
					cnt = 0;
				}
				else
				{
					lcd_write_cmd((0x40 | 0x80));
					cnt = 16;
				}
				return;
			}
		}
	}
	lcd_write_data(c);
	cnt++;
}

/** @brief Writes a string
 */
void piface_puts(char s[])
{
	/* write string */
	int i = 0;
	while (s[i] != '\0')
	{
		piface_putc(s[i]);
		i++;
	}
}

/** @brief Clears the display
 */
void piface_clear(void)
{
	/* clear display */
	cnt = 0;
	lcd_write_cmd(0b00000001);
}

/*
	The methods below are expected to be implemented and used
	during Assignments 2, 3 and 4.
*/

void piface_set_cursor(uint8_t col, uint8_t row)
{
	// return if invalid parameters
	if (row > 1 || row < 0 || col > 15 || col < 0)
		return;

	uint8_t set_cursor_cmd = 0x80; // "Set DDRAM Address": bit 7 set to position the cursor
	uint8_t adr;				   // the position we want to set the cursor to

	if (row == 0)
	{
		adr = col;
		cnt = col;
	}
	else
	{
		adr = 0x40 | col; // 0x40 is the position to row 1 col 0
		cnt = col + 16;
	}

	lcd_write_cmd(set_cursor_cmd | adr);
}

void print_at_seg(int seg, int num)
{
	if (seg < 0 || seg > 3)
		return;
	if (num > 99999)
		return;

	piface_clear_seg(seg);
	piface_set_cursor_at_seg(seg);
	PUTTOLDC("S%d:%d", seg, num);
}

void piface_set_cursor_at_seg(int seg)
{
	if (seg < 0 || seg > 3)
		return;

	int col = 0;
	int row = 0;

	if (seg == 1 || seg == 3)
	{
		col = 8;
	}
	if (seg == 2 || seg == 3)
	{
		row = 1;
	}

	piface_set_cursor(col, row);
}

void piface_clear_seg(int seg)
{
	if (seg < 0 || seg > 3)
		return;

	piface_set_cursor_at_seg(seg);
	PUTTOLDC("        ");
}

void printf_at_seg(int seg, const char *fmt, ...)
{
	if (seg < 0 || seg > 3)
		return;

	char s[9] = { 0 }; // buffer for 8 characters + null terminator
	va_list args;
	va_start(args, fmt);
	vsnprintf(s, sizeof(s), fmt, args);
	va_end(args);

	piface_clear_seg(seg);
	piface_set_cursor_at_seg(seg);
	piface_puts(s);
}
