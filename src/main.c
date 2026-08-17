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

extern void __interrupt __far IRQ0_handler(void);
extern void __interrupt __far IRQ1_handler(void);

void
cleanup(void)
{
	int i;
	if (VBUF != NULL)
		free(VBUF);

	restoreivt(vect_table);

	vga_mode(0x03);
}

uint8_t far *VGA;
uint8_t *VBUF;

Intvect *vect_table = NULL;

extern volatile uint8_t far keystate[];
extern volatile uint16_t far timer_ms;

typedef struct {
	int x;
	int y;
} Player;

int
main(void)
{
	int i;
	uint8_t *image;
	Player pos = {0, 0};

	vect_table = setvect(0x08, IRQ0_handler);
	if (vect_table == NULL) {
		cleanup();
		fprintf(stderr, "Could not allocate IVT buffer.\n");
		exit(1);
	}

	vect_table = insertivt(vect_table, setvect(0x09, IRQ1_handler));
	if (vect_table == NULL) {
		cleanup();
		fprintf(stderr, "Could not allocate IVT buffer.\n");
		exit(1);
	}

	VGA = (uint8_t far *)0xa0000000;
	VBUF = (uint8_t *)malloc(64000);
	if (VBUF == NULL) {
		cleanup();
		fprintf(stderr, "Could not allocate video memory.\n");
		exit(1);
	}

	init_tables();
	init_PIT(18643);	/* ~64hz */
	vga_mode(0x13);

	image = loadimage("uv.128", 128, 128);
	if (image == NULL) {
		cleanup();
		fprintf(stderr, "Could not load texture.\n");
		exit(1);
	}

	while (!keystate[K_ESC]) {
		clearbuffer(VBUF);

		pos.y -= keystate[K_W];
		pos.x -= keystate[K_A];
		pos.y += keystate[K_S];
		pos.x += keystate[K_D];

		drawimage(image, 128, 128, pos.x, pos.y);


		wait_for_vsync();
		bufferswap(VBUF);
	}

	free(image);

	cleanup();
	return 0;
}
