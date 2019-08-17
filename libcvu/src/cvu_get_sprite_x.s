; (c) 2005 Philipp Krause pkk@spth.de

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

.module cvu_get_sprite_x

.globl _cvu_get_sprite_x

; int cvu_get_sprite_x(const struct cvu_sprite *sprite);

_cvu_get_sprite_x:
	pop hl
	pop iy
	push iy
	push hl
	ld h, #0
	ld l, 1(iy)
	bit 7, 3(iy)
	ret z
	ld a, l
	add a, #0xe0
	ld l, a
	ld a, h
	adc a, #0xff
	ld h, a
	ret

