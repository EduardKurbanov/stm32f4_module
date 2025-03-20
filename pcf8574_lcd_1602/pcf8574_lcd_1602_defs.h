/*
 * pcf8574_lcd_1602_defs.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef PCF8574_LCD_1602_DEFS_H
#define PCF8574_LCD_1602_DEFS_H


#define _REG_LCD_1602_E_PULSE                           50
#define _REG_LCD_1602_E_DELAY                           50
#define _REG_LCD_1602_ENABLE_BIT                        0x04
#define _REG_LCD_1602_CMD                               0      //����� - �������� �������
#define _REG_LCD_1602_CHR                               1      //����� - �������� ������
#define _REG_LCD_1602_CLEAR_DISPLAY                     0x01      //������ �����, ������� ������, ������ � ����� ������� �������
#define _REG_LCD_1602_RETURN_HOME                       0x02      //������ � ����� ������� �������, ������ �� ���������
#define _REG_LCD_1602_CURSOR_SHIFT_LEFT                 0x04      //����� ������ ���������� ������� ������ ������������� ���������� �� ���� ���������� �����
#define _REG_LCD_1602_CURSOR_SHIFT_RIGHT                0x06      //����� ������ ���������� ������� ������ ������������� ���������� �� ���� ���������� ������
#define _REG_LCD_1602_DISPLAY_ON                        0x08      //������ ���������� ����������� �� ������ ���
#define _REG_LCD_1602_CURSOR_OFF                        0x0C      //����������� ����� �����������, �� ������ �� �����
#define _REG_LCD_1602_RECTANGULAR_CURSOR_SHAPE          0x0D      //����������� ����� �����������, ������ � ���� ������� ��������� ��������������
#define _REG_LCD_1602_LINEAR_CURSOR_SHAPE               0x0E      //����������� ����� �����������, ������ � ���� ������ ����������� ���������� �����
#define _REG_LCD_1602_COMPLEX_CURSOR_SHAPE              0x0F      //����������� ����� �����������, ������ � ���� ��������� �������������� � ��������������
#define _REG_LCD_1602_INIT_4BIT_MODE_STEP1              0x33      // ���������� ������� � 4-������� ������
#define _REG_LCD_1602_INIT_4BIT_MODE_STEP2              0x32      // ������� ������� � 4-������ �����
#define _REG_LCD_1602_4_BIT_INTERFACE_1_LINE            0x20      //����� � ������������ ��� ����� 4 ����� ���� ������
#define _REG_LCD_1602_4_BIT_INTERFACE_2_LINE            0x28      //����� � ������������ ��� ����� 4 ����� ���� ������
#define _REG_LCD_1602_8_BIT_INTERFACE_1_LINE            0x30      //����� � ������������ ��� ����� 8 ����� ���� ������
#define _REG_LCD_1602_8_BIT_INTERFACE_2_LINE            0x38      //����� � ������������ ��� ����� 8 ����� ���� ������
#define _REG_LCD_1602_ACCESS_TO_CGRAM                   0x40-0x7F //������ ������ �� ���� ������� ��������� ��������� 16 ����� ��������


#endif
