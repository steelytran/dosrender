; 8253 PIT IRQ handler
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
.model flat

.data
	public _timer_ms
	_timer_ms dd 0

	public _IRQ0_handler_size
	_IRQ0_handler_size dd IRQ0_handler_end - IRQ0_handler_

.code
	public init_PIT_
init_PIT_ proc
	push eax

	cli

	mov al, 36h
	out 43h, al

	pop eax

	out 40h, al
	mov al, ah
	out 40h, al

	sti

	ret
init_PIT_ endp

	public IRQ0_handler_
IRQ0_handler_ proc
	push ax

	inc dword ptr [_timer_ms]

	mov al, 20h
	out 20h, al

	pop ax
	iretd
IRQ0_handler_ endp
IRQ0_handler_end:
	end
