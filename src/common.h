#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

#define sgn(x) ((x) < 0 ? - 1 : ((x) > 0 ? 1 : 0))

#define PI 3.14159f

typedef struct Intvect Intvect;
struct Intvect {
	uint8_t n;
	void __interrupt __far * isr;
	Intvect *next;
};

void init_tables(void);

Intvect *setvect(uint8_t, void __interrupt __far *);
Intvect *insertivt(Intvect *, Intvect *);
void restoreivt(Intvect *);
extern Intvect * vect_table;

extern void __interrupt __far IRQ0_handler(void);

extern volatile uint16_t far timer_ms;

extern float SIN[360];
extern float COS[360];
extern long SIN_ACOS[1024];

#endif
