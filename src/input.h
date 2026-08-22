/*
 * Copyright (C) 2026 https://github.com/steelytran
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INPUT_H
#define INPUT_H

#include "common.h"

#define K_ESC 0x01
#define K_F1 0x3B
#define K_F2 0x3C
#define K_F3 0x3D
#define K_F4 0x3E
#define K_F5 0x3F
#define K_F6 0x40
#define K_F7 0x41
#define K_F8 0x42
#define K_F9 0x43
#define K_F10 0x44
#define K_GRAVE 0x29
#define K_1 0x02
#define K_2 0x03
#define K_3 0x04
#define K_4 0x05
#define K_5 0x06
#define K_6 0x07
#define K_7 0x08
#define K_8 0x09
#define K_9 0x0A
#define K_0 0x0B
#define K_MINUS 0x0C
#define K_EQUALS 0x0D
#define K_BACKSPACE 0x0E
#define K_TAB 0x0F
#define K_Q 0x10
#define K_W 0x11
#define K_E 0x12
#define K_R 0x13
#define K_T 0x14
#define K_Y 0x15
#define K_U 0x16
#define K_I 0x17
#define K_O 0x18
#define K_P 0x19
#define K_LBRACKET 0x1A
#define K_RBRACKET 0x1B
#define K_LSHIFT 0x2A
#define K_BACKSLASH 0x2B
#define K_LCTRL 0x1D
#define K_A 0x1E
#define K_S 0x1F
#define K_D 0x20
#define K_F 0x21
#define K_G 0x22
#define K_H 0x23
#define K_J 0x24
#define K_K 0x25
#define K_L 0x26
#define K_SEMICOLON 0x27
#define K_APOSTROPHE 0x28
#define K_RETURN 0x1C
#define K_Z 0x2C
#define K_X 0x2D
#define K_C 0x2E
#define K_V 0x2F
#define K_B 0x30
#define K_N 0x31
#define K_M 0x32
#define K_COMMA 0x33
#define K_PERIOD 0x34
#define K_SLASH 0x35
#define K_RSHIFT 0x36
#define K_SPACE 0x39
#define K_INS 0x52
#define K_HOME 0x47
#define K_PGUP 0x49
#define K_DEL 0x53
#define K_END 0x4F
#define K_PGDN 0x51
#define K_UP 0x48
#define K_LEFT 0x4B
#define K_DOWN 0x50
#define K_RIGHT 0x4D

extern void __interrupt IRQ1_handler(void);

extern size_t IRQ1_handler_size;
extern volatile uint8_t keystate[128];

#endif
