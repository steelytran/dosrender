/* keyboard IRQ handler
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
.globl _keystate
_keystate:
	.fill 128, 1, 0

.globl _IRQ1_handler_size
_IRQ1_handler_size:
	.long IRQ1_handler_end - _IRQ1_handler

.section .text
.globl _IRQ1_handler
_IRQ1_handler:
	pushl %eax
	pushl %ebx

	inb $0x60, %al
	movb %al, %ah

	movb $0x20, %al
	outb %al, $0x20

	movzbl %ah, %ebx
	andl $0x007f, %ebx

	testb $0x80, %ah
	jnz break

make:
	movb $1, _keystate(%ebx)
	jmp done

break:
	movb $0, _keystate(%ebx)

done:
	popl %ebx
	popl %eax
	iretl
IRQ1_handler_end:
