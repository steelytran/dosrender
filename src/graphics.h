#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

#define SCREEN_WIDTH 319
#define SCREEN_HEIGHT 199

enum {
	BLACK = 0,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE
};

extern void far wait_for_vsync(void);

void vga_mode(uint8_t);
void pixel(int, int, uint8_t);
void line(int, int, int, int, uint8_t);
void polygon(int*, int, uint8_t);
void rect(int, int, int, int, uint8_t);
void circle(int, int, int, uint8_t);

extern uint8_t far *VGA;
extern uint8_t *VBUF;

#endif
