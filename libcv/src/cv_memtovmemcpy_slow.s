; (c) 2003-2009 Philipp Krause pkk@spth.de

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


; This is the slow graphics memory writing funtion. It needs 8.4 µs per byte.
; It will work in all graphics modes (minimum time dictated by graphics hardware is 8 µs).


.module cv_memtovmemcpy_slow

.globl _cv_memtovmemcpy_slow

; void cv_memtovmemcpy_slow(cv_vmemp dest, void *src, size_t n)

_cv_memtovmemcpy_slow:
	ld hl, #0x2
	add hl, sp
	ld e, (hl)		; src
	inc hl
	ld d, (hl)		; src
	inc hl
	ld b, (hl)		; n
	inc hl
	ld a, (hl)		; n
	ex de, hl
	ld d, a
	or a, b
	jr z, Ende		; n == 0 ?
	ld c, #0xbe	; Port
	ld a, b
	or a
	jr z, Weiter		; n % 256 == 0 ?
	inc d
Weiter:
	outi
	nop
	jp nz, Weiter
	dec d
	jr nz, Weiter
Ende:
	ret

