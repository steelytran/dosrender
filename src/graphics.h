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

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

enum {
	BLACK = 0,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE
};

typedef struct {
	int32_t x;
	int32_t y;
	int32_t z;
} Vertex;

extern void wait_for_vsync(void);
extern void clearbuffer(uint8_t *);
extern void bufferswap(uint8_t *);

void vga_mode(uint8_t);
void pixel(int, int, uint8_t);
void line(int, int, int, int, uint8_t);
void polygon(int *, int, uint8_t);
void rect(int, int, int, int, uint8_t);
void circle(int, int, int, uint8_t);
uint8_t *loadimage(const char * , int, int);
void drawimage(uint8_t * , int, int, int, int);

Vertex rotate2d(const Vertex *);

extern uint8_t *VBUF;

#endif
