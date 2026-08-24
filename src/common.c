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

#include <dpmi.h>
#include <go32.h>

#include "common.h"

Intvect *
setvect(uint8_t n, void *isr){
	Intvect *newp;
	_go32_dpmi_seginfo newISR;

	newp = (Intvect *)malloc(sizeof(Intvect));
	if (newp == NULL)
		return newp;

	_go32_dpmi_get_protected_mode_interrupt_vector(n, &newp->isr);

	newp->n = n;

	newISR.pm_offset = (int)isr;
	newISR.pm_selector = _go32_my_cs();

	_go32_dpmi_set_protected_mode_interrupt_vector(n, &newISR);

	return newp;
}

Intvect *
insertivt(Intvect * list, Intvect * newp) {
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
		_go32_dpmi_set_protected_mode_interrupt_vector(ivt->n, &ivt->isr);
		nextp = ivt->next;

		free(ivt);

		ivt = nextp;
	}
}
