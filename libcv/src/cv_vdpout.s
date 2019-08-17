; (c) 2005-2009 Philipp Krause pkk@spth.de

;	This library is free software; you can redistribute it and/or modify it
;	under the terms of the GNU Library General Public License as published by the
;	Free Software Foundation; either version 2, or (at your option) any
;	later version.
   
;	This library is distributed in the hope that it will be useful,
;	but WITHOUT ANY WARRANTY; without even the implied warranty of
;	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;	GNU Library General Public License for more details.
   
;	You should have received a copy of the GNU Library General Public License
;	along with this program; if not, write to the Free Software
;	Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

.module cv_vdpout

.globl _cv_vdpout

; void vdpout(const u_int8_t reg, const u_int8_t data1)

_cv_vdpout:
	pop hl
	pop bc				; reg in c, data in b
	push bc
write:
	in a, (0xbf)			; Read status port to reset register access counter.
	xor a, a
	ld (#_cv_vint_indicator), a
	ld a, b
	out(0xbf), a			; write data
	ld a, #0x80			; set most significant bit - assume second most significant bit is cleared.
	or a, c
	out(0xbf), a			; choose register to update with data
	ld a, (#_cv_vint_indicator)
	or a, a
	jr nz, write
	jp (hl)				; return

