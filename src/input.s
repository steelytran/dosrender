;; Keyboard IRQ handler
;; Copyright (C) 2026 https://github.com/steelytran
;; 
;; This program is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.
;; 
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;; 
;; You should have received a copy of the GNU General Public License
;; along with this program.  if not, see <http://www.gnu.org/licenses/>.

.model large

.data
	public _keystate
	_keystate db 128 dup(0)

.code
	public IRQ1_handler_
IRQ1_handler_ proc far
	push ax
	push bx
	push ds

	mov ax, @data
	mov ds, ax

	in al, 60h
	mov ah, al

	mov al, 20h
	out 20h, al

	mov al, ah
	mov bx, ax
	and bx, 007fh

	test al, 80h
	jnz break

make:
	mov byte ptr [_keystate + bx], 1
	jmp done

break:
	mov byte ptr [_keystate + bx], 0

done:
	pop ds
	pop bx
	pop ax
	iret
IRQ1_handler_ endp
	end
