CC=wcc
AS=wasm
LD=wlink

export WATCOM=/usr/local/src/open-watcom-v2/rel
INCLUDE=$(WATCOM)/h

CFLAGS=-os -d2 -ml -q -i=$(INCLUDE)
LDFLAGS=sys dos

OBJS=\
src/obj/input.s.obj \
src/obj/draw.c.obj \
src/obj/main.c.obj \
src/obj/common.c.obj \
src/obj/timer.s.obj \
src/obj/draw.s.obj

.PHONY: all clean
.SUFFIXES: .obj .c. .s

all: $(OBJS)
	$(LD) $(LDFLAGS) name bin/a.exe file { $(OBJS) }

src/obj/%.c.obj: src/%.c
	$(CC) $(CFLAGS) -fo=$@ $<

src/obj/%.s.obj: src/%.s
	$(AS) -fo=$@ $<

clean:
	rm -f src/obj/* *.err
