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
end
