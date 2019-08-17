; (c) 2003 - 2007 Philipp Klaus Krause philipp@colecovision.eu

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


; This is the slow graphics memory setting funtion. It needs 8.4 µs per byte.


.module cv_vmemset_slow

.globl _cv_vmemset_slow

; void cv_vmemset_slow(int c, size_t n);

_cv_vmemset_slow:	
	pop hl
	pop de	; c
	pop bc	; n
	push bc
	push de
	ld a, b
	ld b, c
	ld c, a
	or a, b
	jr z, Ende
	ld a, b
	or a
	ld a, e
	jr z, Weiter
	inc c
Weiter:
	out (0xbe), a
	dec	de	; delay by 6 cycles
	djnz Weiter
	dec c
	jr nz, Weiter
Ende:
	jp (hl)

