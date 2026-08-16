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
#include <stdlib.h>
#include <dos.h>

#include "common.h"

Intvect
* setvect(uint8_t n, void __interrupt __far * isr){
	Intvect *newp;

	newp = (Intvect *) malloc(sizeof(Intvect));
	if (newp == NULL)
		return newp;

	newp->n = n;
	newp->isr = _dos_getvect(n);

	_dos_setvect(n, isr);

	return newp;
}

Intvect
* insertivt(Intvect * list, Intvect * newp) {
	if (newp == NULL)
		return newp;

	newp->next = list;
	return newp;
}

void
restoreivt(Intvect * ivt)
{
	Intvect *nextp;

	while (ivt != NULL) {
		_dos_setvect(ivt->n, ivt->isr);

		nextp = ivt->next;

		free(ivt);

		ivt = nextp;
	}
}
