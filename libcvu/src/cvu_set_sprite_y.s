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

.module cvu_set_sprite_y

.globl _cvu_set_sprite_y

; void cvu_set_sprite_y(struct cvu_sprite *sprite, int y);

_cvu_set_sprite_y:
	pop iy
	pop hl
	pop bc
	push bc
	push hl

;if(y > 207)
;	y = 207;
	ld a, #207
	sub a, c
	ld a, #0
	sbc a, b
	jp p, g207c
	ld b, #0
	ld c, #207
g207c:

;if(y < -32)
;	y = -32;
	ld a, c
	sub a, #0xe0
	ld a, b
	sbc a, #0xff
	jp p, g32c
	ld b, #0xff
	ld c, #0xe0
g32c:

;if(y < 0)
;	y += 256;
	;bit 7, b
	;jp z, g0c
	;dec c
	;inc b
;g0c:

; sprite->y = y;
	ld(hl), c

	jp(iy)

