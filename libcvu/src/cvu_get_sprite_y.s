; (c) 2008 - 2010 Philipp Klaus Krause philipp@colecovision.eu

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

.module cvu_get_sprite_y

.globl _cvu_get_sprite_y

; int cvu_get_sprite_y(const struct cvu_sprite *sprite);

_cvu_get_sprite_y:
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	l, (hl)
	ld	h, #0
	ld	a, l
	sub	a, #0xdf
	ret	C
	ld	bc, #0xff00
	add	hl, bc
	ret

