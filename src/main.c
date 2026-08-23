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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "common.h"
#include "graphics.h"
#include "input.h"

extern void __interrupt IRQ0_handler(void);
extern void __interrupt IRQ1_handler(void);

uint8_t *VGA;
uint8_t *VBUF = NULL;

Intvect *vect_table = NULL;

extern volatile uint8_t keystate[128];
extern size_t IRQ1_handler_size;
extern size_t IRQ0_handler_size;
extern volatile uint32_t timer_ms;

Player pov = {0, 0, 0, 0};

int
main(void)
{
	int status = 0;
	uint8_t *image = NULL;
	Vertex triangle_s[3];
	Vertex triangle[] = {
		{30, 50, 0},
		{10, 190, 0},
		{270, 60, 0}
	};

	if (dpmi_lock_memory((void *)&timer_ms, sizeof(uint32_t)) != 0)
		return 1;

	if (dpmi_lock_memory((void *)IRQ0_handler, IRQ0_handler_size) != 0)
		return 1;

	if (dpmi_lock_memory((void *)IRQ1_handler, IRQ1_handler_size) != 0)
		return 1;

	if (dpmi_lock_memory((void *)keystate, sizeof(uint8_t) * 128) != 0)
		return 1;

	vect_table = setvect(0x08, IRQ0_handler);
	if (vect_table == NULL) {
		status = -1;
		goto cleanup;
	}

	vect_table = insertivt(vect_table, setvect(0x09, IRQ1_handler));
	if (vect_table == NULL) {
		status = -1;
		goto cleanup;
	}

	VGA = (uint8_t *)0xa0000;
	VBUF = (uint8_t *)malloc(64000);
	if (VBUF == NULL) {
		status = -1;
		goto cleanup;
	}

	init_tables();
	init_PIT(18643);	/* ~64hz */
	vga_mode(0x13);

	image = loadimage("uv.128", 128, 128);
	if (image == NULL) {
		status = -1;
		goto cleanup;
	}

	while (!keystate[K_ESC]) {
		memset(VBUF, 0, 64000);

		pov.angle -= keystate[K_RIGHT];
		pov.angle += keystate[K_LEFT];
		pov.angle %= 360;
		if (pov.angle < 0)
			pov.angle = 359;

		if (keystate[K_W]) {
			pov.y -= (int32_t)(COS[pov.angle] * FP_SCALE * 2);
			pov.x -= (int32_t)(SIN[pov.angle] * FP_SCALE * 2);
		}
		if (keystate[K_A]) {
			pov.y -= (int32_t)(COS[(pov.angle + 90) % 360] * FP_SCALE * 2);
			pov.x -= (int32_t)(SIN[(pov.angle + 90) % 360] * FP_SCALE * 2);
		}
		if (keystate[K_S]) {
			pov.y += (int32_t)(COS[pov.angle] * FP_SCALE * 2);
			pov.x += (int32_t)(SIN[pov.angle] * FP_SCALE * 2);
		}
		if (keystate[K_D]) {
			pov.y += (int32_t)(COS[(pov.angle + 90) % 360] * FP_SCALE * 2);
			pov.x += (int32_t)(SIN[(pov.angle + 90) % 360] * FP_SCALE * 2);
		}

		triangle_s[0] = rotate2d(&triangle[0]);
		triangle_s[1] = rotate2d(&triangle[1]);
		triangle_s[2] = rotate2d(&triangle[2]);


		line(
			triangle_s[0].x,
			triangle_s[0].y,
			triangle_s[1].x,
			triangle_s[1].y, 
			WHITE
		);
		line(
			triangle_s[1].x,
			triangle_s[1].y, 
			triangle_s[2].x,
			triangle_s[2].y,
			WHITE
		);
		line(
			triangle_s[2].x,
			triangle_s[2].y,
			triangle_s[0].x,
			triangle_s[0].y,
			WHITE
		);

		pixel(160, 100, CYAN);

		wait_for_vsync();
		memcpy(VGA, VBUF, 64000);
	}

cleanup:
	vga_mode(0x03);
	restoreivt(vect_table);
	free(image);
	free(VBUF);

	return status;
}
