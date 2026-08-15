.model large

.data
	public _keystate
	_keystate db 128 dup(0)

.code
	public isr09h_
isr09h_ proc far
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
isr09h_ endp
	end
