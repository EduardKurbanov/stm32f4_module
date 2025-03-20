/*
 * pcf8574_lcd_1602.c
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#include "pcf8574_lcd_1602.h"
#include "pcf8574_lcd_1602_defs.h"
#include "i2c.h"


// Function to toggle the enable bit
static void pcf8574_lcd_1602_toggle_enable(uint8_t bits)
{
    HAL_Delay(1);
    uint8_t enable_bit = bits | _REG_LCD_1602_ENABLE_BIT;
    HAL_I2C_Master_Transmit(_BUS_HANDLER_I2C_PCF8574_LCD_1602, _DEVICE_ADDRESS_PCF8574_LCD_1602 << 1, &enable_bit, 1, 100);
    HAL_Delay(1);
    enable_bit = bits & ~_REG_LCD_1602_ENABLE_BIT;
    HAL_I2C_Master_Transmit(_BUS_HANDLER_I2C_PCF8574_LCD_1602, _DEVICE_ADDRESS_PCF8574_LCD_1602 << 1, &enable_bit, 1, 100);
    HAL_Delay(1);
}

// Function to send a byte to the LCD
static void pcf8574_lcd_1602_byte(uint8_t bits, uint8_t mode)
{
    uint8_t bits_high = mode | (bits & 0xF0) | _REG_LCD_1602_DISPLAY_ON;
    uint8_t bits_low = mode | ((bits << 4) & 0xF0) | _REG_LCD_1602_DISPLAY_ON;

    // Send high bits
    HAL_I2C_Master_Transmit(_BUS_HANDLER_I2C_PCF8574_LCD_1602, _DEVICE_ADDRESS_PCF8574_LCD_1602 << 1, &bits_high, 1, 100);
    pcf8574_lcd_1602_toggle_enable(bits_high);

    // Send low bits
    HAL_I2C_Master_Transmit(_BUS_HANDLER_I2C_PCF8574_LCD_1602, _DEVICE_ADDRESS_PCF8574_LCD_1602 << 1, &bits_low, 1, 100);
    pcf8574_lcd_1602_toggle_enable(bits_low);
}

// Function to send a string to the LCD
void pcf8574_lcd_1602_string(const char *message, uint8_t line)
{
    pcf8574_lcd_1602_byte(line, _REG_LCD_1602_CMD);

    for (int i = 0; i < _REG_LCD_1602_LCD_WIDTH && message[i] != '\0'; i++)
    {
        pcf8574_lcd_1602_byte(message[i], _REG_LCD_1602_CHR);
    }
}

// Function to clear the LCD display
void pcf8574_lcd_1602_clear(void)
{
	pcf8574_lcd_1602_byte(_REG_LCD_1602_CLEAR_DISPLAY, _REG_LCD_1602_CMD);  // Clear display command
    HAL_Delay(5);
}

// Function to create a custom character
void pcf8574_lcd_1602_create_custom_char(uint8_t location, uint8_t *charmap)
{
    // Ensure the location is between 0 and 7
    if (location >= 8)
        return;

    // Set the LCD to CGRAM mode (Character Generator RAM)
    pcf8574_lcd_1602_byte(0x40 | (location << 3), _REG_LCD_1602_CMD); // Set CGRAM address

    // Write the custom character pattern to CGRAM
    for (int i = 0; i < 8; i++)
    {
        pcf8574_lcd_1602_byte(charmap[i], _REG_LCD_1602_CHR); // Send each byte
    }
}

// Function to display a custom character
void pcf8574_lcd_1602_display_custom_char(uint8_t line, uint8_t pos, uint8_t location)
{
    // Set the cursor position on the specified line and position
    if (line == 0)
    {
        pcf8574_lcd_1602_byte(0x80 + pos, _REG_LCD_1602_CMD);  // Line 1, position 'pos'
    }
    else if (line == 1)
    {
        pcf8574_lcd_1602_byte(0xC0 + pos, _REG_LCD_1602_CMD);  // Line 2, position 'pos'
    }

    // Display the custom character (use the location of the custom character)
    pcf8574_lcd_1602_byte(location, _REG_LCD_1602_CHR);
}

// Function to initialize LCD
void pcf8574_lcd_1602_init(void)
{
    HAL_Delay(50);  // Wait for >40ms
    pcf8574_lcd_1602_byte(_REG_LCD_1602_INIT_4BIT_MODE_STEP1, _REG_LCD_1602_CMD);    // Initialise in 4-bit mode
    pcf8574_lcd_1602_byte(_REG_LCD_1602_INIT_4BIT_MODE_STEP2, _REG_LCD_1602_CMD);    // Initialise in 4-bit mode
    pcf8574_lcd_1602_byte(_REG_LCD_1602_CURSOR_SHIFT_RIGHT, _REG_LCD_1602_CMD);      // Cursor move direction
    pcf8574_lcd_1602_byte(_REG_LCD_1602_CURSOR_OFF, _REG_LCD_1602_CMD);              // Display On, Cursor Off, Blink Off
    pcf8574_lcd_1602_byte(_REG_LCD_1602_4_BIT_INTERFACE_2_LINE, _REG_LCD_1602_CMD);  // Function set: 4-bit mode, 2 lines, 5x8 font
    pcf8574_lcd_1602_byte(_REG_LCD_1602_CLEAR_DISPLAY, _REG_LCD_1602_CMD);           // Clear display
    HAL_Delay(5);
}
