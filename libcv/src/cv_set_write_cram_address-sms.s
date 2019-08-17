; (c) 2016 Philipp Klaus Krause philipp@colecovision.eu

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

.module cv_set_write_cram_address

.globl _cv_set_write_cram_address

; void cv_set_write_cram_address(cv_cmemp address);

_cv_set_write_cram_address:
	pop iy
	pop hl
	push hl
write:
	in a, (0xbf)	; reset register access counter.
	xor a, a
	ld (#_cv_vint_indicator), a
	ld a, l
	out (0xbf), a
	ld a, #0xc0
	out (0xbf), a
	ld a, (#_cv_vint_indicator)
	or a, a
	jp nz, write
	jp (iy)

