/* 8253 PIT IRQ handler
 * Copyright (C) 2026 https://github.com/steelytran
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

.section .data
.globl _timer_ms
_timer_ms:
	.long 0

.globl _IRQ0_handler_size
_IRQ0_handler_size:
	.long IRQ0_handler_end - _IRQ0_handler

.section .text
.globl _init_PIT
_init_PIT:
	pushl %eax

	cli

	movb $0x36, %al
	outb %al, $0x43

	popl %eax

	outb %al, $0x40
	movb %ah, %al
	outb %al, $0x40

	sti
	ret

.globl _IRQ0_handler
_IRQ0_handler:
	pushl %eax

	incl _timer_ms

	movb $0x20, %al
	outb %al, $0x20

	popl %eax
	iretl
IRQ0_handler_end:
