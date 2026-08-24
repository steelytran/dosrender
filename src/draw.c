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

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <dpmi.h>
#include <go32.h>
#include <sys/farptr.h>

#include "graphics.h"
#include "common.h"

void vga_mode(uint8_t mode);
void init_tables();
void pixel(int x, int y, uint8_t color);
void line(int x1, int y1, int x2, int y2, uint8_t color);
void polygon(int *vertices, int n, uint8_t color);
void rect(int x1, int y1, int x2, int y2, uint8_t color);
void circle(int x, int y, int radius, uint8_t color);
uint8_t *loadimage(const char *path, int w, int h);
void drawimage(uint8_t *image, int w, int h, int x, int y);

extern uint8_t *VBUF;

float SIN[360];
float COS[360];
long SIN_ACOS[1024];

void
init_tables()
{
	int i;

	for (i = 0; i < 360; i++) {
		SIN[i] = sin((float)i / 180 * PI);
		COS[i] = cos((float)i / 180 * PI);
	}
	for (i = 0; i < 1024; i++)
		SIN_ACOS[i] = sin(acos((float)i / 1024)) * 0x10000L;
}

void
vga_mode(uint8_t mode)
{
	__dpmi_regs r;
	r.x.ax = mode;
	__dpmi_int(0x10, &r);
}

void inline
pixel(int x, int y, uint8_t color)
{
	if (x >= 0 && x < 320 && y >= 0 && y < 200)
		VBUF[(y << 8) + (y << 6) + x] = color;
}

void
line(int x1, int y1, int x2, int y2, uint8_t color)
{
	int i;
	int dx = x2 - x1;
	int dy = y2 - y1;
	int u_dx = abs(dx);
	int u_dy = abs(dy);
	int sdx = sgn(dx);
	int sdy = sgn(dy);
	int px = u_dx >> 1;
	int py = u_dy >> 1;
	int x = x1;
	int y = y1;

	pixel(x, y, color);

	if (u_dx >= u_dy) {
		for (i = 0; i < u_dx; i++) {
			py += u_dy;
			if (py >= u_dx) {
				py -= u_dx;
				y += sdy;
			}
			x += sdx;
			pixel(x, y, color);
		}
	} else {
		for (i = 0; i < u_dy; i++) {
			px += u_dx;
			if (px >= u_dy) {
				px -= u_dy;
				x += sdx;
			}
			y += sdy;
			pixel(x, y, color);
		}
	}
}

void
polygon(int *vertices, int n, uint8_t color)
{
	int i;
	int x1, y1, x2, y2;
	for (i = 0; i < n - 1; i++) {
		x1 = vertices[0 + (i << 1)];
		y1 = vertices[1 + (i << 1)];
		x2 = vertices[2 + (i << 1)];
		y2 = vertices[3 + (i << 1)];
		line(x1, y1, x2, y2, color);
	}
	x1 = vertices[0],
		y1 = vertices[1],
		x2 = vertices[(n << 1) - 2],
		y2 = vertices[(n << 1) - 1],
		line(x1, y1, x2, y2, color);
}

void
rect(int x1, int y1, int x2, int y2, uint8_t color)
{
	int i, j;
	int dx = x1 - x2;
	int dy = y1 - y2;
	int u_dx = abs(dx);
	int u_dy = abs(dy);
	int sgn_x = sgn(dx);
	int sgn_y = sgn(dy);
	int x[2];
	int y[2];

	x[0] = x1;
	y[0] = y1;
	x[1] = x2;
	y[1] = y2;

	for (i = 0; i < 2; i++) {

		for (j = 0; j <= u_dx; j++)
			pixel(x[0] - (j * sgn_x), y[i], color);
		for (j = 0; j <= u_dy; j++)
			pixel(x[i], y[0] - (j * sgn_y), color);
	}
}

void
circle(int x, int y, int radius, uint8_t color)
{
	long n, invradius;
	int dx, dy;
	unsigned short dxoffset, dyoffset, offset;

	n = 0;
	invradius = (1 / (float)radius) * 0x10000L;
	dy = radius - 1;
	offset = (y << 8) + (y << 6) + x;

	for (dx = 0; dx <= dy; dx++) {
		dxoffset = (dx << 8) + (dx << 6);
		dyoffset = (dy << 8) + (dy << 6);
		VBUF[offset + dy - dxoffset] = color;
		VBUF[offset + dx - dyoffset] = color;
		VBUF[offset - dx - dyoffset] = color;
		VBUF[offset - dy - dxoffset] = color;
		VBUF[offset - dy + dxoffset] = color;
		VBUF[offset - dx + dyoffset] = color;
		VBUF[offset + dx + dyoffset] = color;
		VBUF[offset + dy + dxoffset] = color;
		n += invradius;
		dy = (int)((radius * SIN_ACOS[(int)(n >> 6)]) >> 16);
	}
}

uint8_t *
loadimage(const char *path, int w, int h)
{
	uint8_t *mem;
	FILE *image;

	image = fopen(path, "rb");
	if (image == NULL)
		return NULL;


	mem = (uint8_t *)malloc(w * h);
	if (mem == NULL)
		return mem;

	fread(mem, 1, w * h, image);

	fclose(image);

	return mem;
}

void
drawimage(uint8_t *image, int w, int h, int x, int y)
{
	int i;
	uint8_t *screen;
	int original_w = w;

	if (x >= SCREEN_WIDTH || x + w < 0 || y >= SCREEN_HEIGHT || y + h < 0)
		return;

	if (x < 0) {
		image -= x;
		w += x;
		x = 0;
	}

	if (y < 0) {
		image -= y * original_w;
		h += y;
		y = 0;
	}
	if (x + w >= SCREEN_WIDTH)
		w = SCREEN_WIDTH - x;

	if (y + h >= SCREEN_HEIGHT)
		h = SCREEN_HEIGHT - y;

	screen = &VBUF[(y << 8) + (y << 6) + x];

	for (i = 0; i < h; i++) {
		memcpy(screen, image, w);
		screen += SCREEN_WIDTH;
		image += original_w;
	}
}
