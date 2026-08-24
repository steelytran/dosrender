DJGPP=/usr/local/djgpp/bin/i586-pc-msdosdjgpp

CC = $(DJGPP)-gcc
AS = $(DJGPP)-gcc
LD = $(DJGPP)-gcc

CFLAGS = -O1
LDFLAGS =

OBJS =\
src/obj/main.c.obj \
src/obj/draw.c.obj \
src/obj/input.S.obj \
src/obj/common.c.obj \
src/obj/timer.S.obj \
src/obj/render.c.obj \

.PHONY: all clean
.SUFFIXES: .obj .c. .S

all: $(OBJS)
	$(LD) $(LDFLAGS) -o bin/a.exe $(OBJS)

src/obj/%.c.obj: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/obj/%.S.obj: src/%.S
	$(AS) -c -o $@ $<

clean:
	rm -f src/obj/* *.err
