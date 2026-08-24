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

#ifndef COMMON_H
#define COMMON_H

#include <dpmi.h>
#include <stdint.h>
#include <stddef.h>

#define sgn(x) ((x) < 0 ? - 1 : ((x) > 0 ? 1 : 0))

#define FP_FACTOR 12
#define FP_SCALE (1 << FP_FACTOR)

typedef struct Intvect Intvect;
struct Intvect {
	uint8_t n;
	_go32_dpmi_seginfo isr;
	Intvect *next;
};

typedef struct {
	int32_t x;
	int32_t y;
	int32_t z;
	int32_t angle;
} Player;

extern Player pov;

void init_tables(void);

Intvect *setvect(uint8_t, void *);
Intvect *insertivt(Intvect *, Intvect *);
void restoreivt(Intvect *);
extern Intvect * vect_table;

extern void IRQ0_handler(void);
extern void init_PIT(uint32_t);

extern volatile uint32_t timer_ms;

extern float SIN[360];
extern float COS[360];
extern long SIN_ACOS[1024];

#endif
