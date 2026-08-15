;; 8253 PIT IRQ handler
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
	public _timer_ms
	_timer_ms dw 0

.code
	public init_PIT_
init_PIT_ proc far
	ret
init_PIT_ endp

	public IRQ0_handler_
IRQ0_handler_ proc far
	push ax
	push ds

	mov ax, @data
	mov ds, ax

	inc word ptr [_timer_ms]

	mov al, 20h
	out 20h, al

	pop ds
	pop ax
	iret
IRQ0_handler_ endp
	end
