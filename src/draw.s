;
; Copyright (C) 2026 https://github.com/steelytran
;
; This program is free software: you can redistribute it and/or modify it
; under the terms of the GNU General Public License as published by the Free
; Software Foundation, either version 3 of the License, or (at your option)
; any later version.
;
; This program is distributed in the hope that it will be useful, but
; WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
; or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
; for more details.
;
; You should have received a copy of the GNU General Public License along
; with this program.  If not, see <http://www.gnu.org/licenses/>.
;
.model large

.code
	public wait_for_vsync_
wait_for_vsync_ proc far
	push ax
	push dx

	mov dx, 03dah

trace_end:
	in ax, dx
	test ax, 08h
	jnz trace_end

trace_start:
	in ax, dx
	test ax, 08h
	jz trace_start

	pop dx
	pop ax
	ret
wait_for_vsync_ endp

	public clearbuffer_
clearbuffer_ proc far
	push es
	push di

	mov es, dx
	mov di, ax

	mov ax, 00h

	mov cx, 32000

	rep stosw

	pop di
	pop es
	ret
clearbuffer_ endp

	public bufferswap_
bufferswap_ proc far
	push ds
	push es
	push si
	push di

	mov ds, dx
	mov si, ax

	mov ax, 0a000h
	mov es, ax
	xor di, di

	mov cx, 32000

	rep movsw

	pop di
	pop si
	pop es
	pop ds
	ret
bufferswap_ endp

;	public drawimage_
;drawimage_ proc far
; uint8_t *image, int cx, int bx, int dx, int ax)
; {
; 	int i;
; 
; 	uint8_t *screen = &VBUF[(ax << 8) + (ax << 6) + dx];
; 
; 	for (i = 0; i < bx; i++) {
; 		memcpy(screen, image, cx);
; 		screen += SCREEN_WIDTH;
; 		image += cx;
; 	}
; }
;drawimage_ endp
end
