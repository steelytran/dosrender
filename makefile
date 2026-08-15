CC=wcc
AS=wasm
LD=wlink

export WATCOM=/usr/local/src/open-watcom-v2/rel
INCLUDE=$(WATCOM)/h

CFLAGS=-os -d0 -ml -i=$(INCLUDE)
LDFLAGS=sys dos

OBJS=\
src/obj/input.obj \
src/obj/draw.obj \
src/obj/main.obj \
src/obj/vsync.obj \
src/obj/common.obj \
src/obj/timer.obj

.PHONY: all clean
.SUFFIXES: .obj .c. .s

all: $(OBJS)
	$(LD) $(LDFLAGS) name bin/a.exe file { $(OBJS) }

src/obj/%.obj: src/%.c
	$(CC) $(CFLAGS) -fo=$@ $<

src/obj/%.obj: src/%.s
	$(AS) -fo=$@ $<

clean:
	rm -f src/obj/* *.err
