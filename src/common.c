#include <stdint.h>
#include <stdlib.h>
#include <dos.h>

#include "common.h"

Intvect
*setivt(uint8_t n, void __interrupt __far *isr)
{
	Intvect *newp;

	newp = (Intvect*)malloc(sizeof(Intvect));
	if (newp == NULL)
		return newp;

	newp->n = n;
	newp->isr = _dos_getvect(n);

	_dos_setvect(n, isr);

	return newp;
}

void
restoreivt(Intvect *ivt)
{
	for (; ivt->next != NULL; ivt = ivt->next) {
		_dos_setvect(ivt->n, ivt->isr);
	}
	_dos_setvect(ivt->n, ivt->isr);
}
