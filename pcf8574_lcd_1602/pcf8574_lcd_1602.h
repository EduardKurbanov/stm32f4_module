/*
 * pcf8574_lcd_1602.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */
/*
* include "pcf8574_lcd_1602.h"
* 
* pcf8574_lcd_1602_init();
* 
* int main(void)
* {
*       pcf8574_lcd_1602_string("hello", _REG_LCD_1602_LCD_LINE_0);
*       pcf8574_lcd_1602_string("world", _REG_LCD_1602_LCD_LINE_1 + 6);
* 
*		return 0;
* }
*/

#ifndef PCF8574_LCD_1602_H
#define PCF8574_LCD_1602_H

#include <inttypes.h>

#define _DEVICE_ADDRESS_PCF8574_LCD_1602                 0x27
#define _BUS_HANDLER_I2C_PCF8574_LCD_1602                &hi2c1

#define _REG_LCD_1602_LCD_WIDTH                          16
#define _REG_LCD_1602_LCD_LINE_0                         0x80      // LCD RAM address for the 1st line
#define _REG_LCD_1602_LCD_LINE_1                         0xC0      // LCD RAM address for the 2nd line
#define _REG_LCD_1602_LCD_LINE_2                         0x94      // LCD RAM address for the 3rd line
#define _REG_LCD_1602_LCD_LINE_3                         0xD4      // LCD RAM address for the 4th line

//    - | 0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
//   00 |0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F
//   01 |0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF

typedef enum
{
    E_BACKLIGHT_SWITCH_ON = 0,
    E_BACKLIGHT_SWITCH_OFF = 1
}E_BACKLIGHT_SWITCH_STATUS;

void pcf8574_lcd_1602_init(void);
void pcf8574_lcd_1602_string(const char *message, uint8_t line);
void pcf8574_lcd_1602_clear(void);
void pcf8574_lcd_1602_create_custom_char(uint8_t location, uint8_t *charmap);
void pcf8574_lcd_1602_display_custom_char(uint8_t line, uint8_t pos, uint8_t location);


#endif
