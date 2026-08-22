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
.386p
.model flat

.code
	public wait_for_vsync_
wait_for_vsync_ proc
	mov dx, 03dah

trace_end:
	in al, dx
	test al, 08h
	jnz trace_end

trace_start:
	in al, dx
	test al, 08h
	jz trace_start

	ret
wait_for_vsync_ endp
end
