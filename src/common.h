#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

#define sgn(x) ((x) < 0 ? - 1 : ((x) > 0 ? 1 : 0))

#define PI 3.14159f

typedef struct Intvect Intvect;
struct Intvect {
	uint8_t n;
	void __interrupt __far *isr;
	Intvect *next;
};

Intvect *setivt(uint8_t, void __interrupt __far*);
void restoreivt(Intvect*);

void init_tables(void);

extern Intvect *vect_table;

extern float SIN[360];
extern float COS[360];
extern long SIN_ACOS[1024];

#endif
