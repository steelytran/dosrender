; Keyboard IRQ handler
; Copyright (C) 2026 https://github.com/steelytran
; 
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
; 
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with this program.  if not, see <http://www.gnu.org/licenses/>.

.386p
.MODEL FLAT

.DATA
	PUBLIC _keystate
	_keystate db 128 dup(0)

	PUBLIC _IRQ1_handler_size
	_IRQ1_handler_size dd IRQ1_handler_end - IRQ1_handler_

.CODE
	PUBLIC IRQ1_handler_
IRQ1_handler_ PROC
	push eax
	push ebx

	in al, 60h
	mov ah, al

	mov al, 20h
	out 20h, al

	movzx ebx, ah
	and ebx, 007fh

	test ah, 80h
	jnz break

make:
	mov byte ptr [_keystate + ebx], 1
	jmp done

break:
	mov byte ptr [_keystate + ebx], 0

done:
	pop ebx
	pop eax
	iretd
IRQ1_handler_ ENDP
IRQ1_handler_end:
	END
