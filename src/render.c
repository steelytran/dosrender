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

#include <stdint.h>

#include "graphics.h"
#include "common.h"

extern Player pov;

Vertex
rotate2d(const Vertex *v)
{
	Vertex new = *v;

	int32_t dx = (v->x << FP_FACTOR) - pov.x;
	int32_t dy = (v->y << FP_FACTOR) - pov.y;

	new.x = (int32_t)(dx * COS[pov.angle] - dy * SIN[pov.angle]);
	new.y = (int32_t)(dx * SIN[pov.angle] + dy * COS[pov.angle]);

	new.x = (new.x >> FP_FACTOR) + 160;
	new.y = (new.y >> FP_FACTOR) + 100;
	return new;
}
