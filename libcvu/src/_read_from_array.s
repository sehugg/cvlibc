; (c) 2006 Philipp Krause pkk@spth.de

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

.module _read_from_array

.globl __read_from_array

; uint8_t _read_from_array(void);

__read_from_array:
	ld	hl, (__common_state)
	ld	bc, #0xf
	add	hl, bc
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, (de)
	inc	de
	ld	(hl), d
	dec	hl
	ld	(hl), e
	ld	l, a
	ret

