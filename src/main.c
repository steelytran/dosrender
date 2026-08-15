/*
 * Copyright (C) 2026 https://github.com/steelytran
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "common.h"
#include "graphics.h"
#include "input.h"

extern void __interrupt __far isr09h(void);

void
quit(int e)
{
	int i;
	if (VBUF != NULL)
		free(VBUF);

	restoreivt(vect_table);

	vga_mode(0x03);
	exit(e);
}

uint8_t far *VGA;
uint8_t *VBUF;
//ISR *IVT;

Intvect *vect_table = NULL;

extern volatile uint8_t far keystate[];

int
main(int argc, char *argv[])
{
	int i;

	vect_table = setivt(0x09, isr09h);
	if (vect_table == NULL) {
		fprintf(stderr, "Could not allocate IVT buffer.\n");
		quit(1);
	}

	VGA = (uint8_t far*) 0xa0000000;
	VBUF = (uint8_t*) malloc(64000);
	if (VBUF == NULL) {
		fprintf(stderr, "Could not allocate video memory.\n");
		quit(1);
	}

	init_tables();
	vga_mode(0x13);

	while (!keystate[K_ESC]) {
		memset(VBUF, 0, 64000);

		line(0, 0, 50, 50, RED);

		wait_for_vsync();
		_fmemcpy(VGA, VBUF, 64000);
	}

	quit(0);
	return 0;
}
