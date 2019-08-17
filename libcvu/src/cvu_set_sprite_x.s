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

.module cvu_set_sprite_x

.globl _cvu_set_sprite_x

; void cvu_set_sprite_y(struct cvu_sprite *sprite, int x);

_cvu_set_sprite_x:
	pop hl
	pop iy
	pop bc
	push bc
	push iy

;if(x < -32)
;	x = -32
	ld a, c
	sub a, #0xe0
	ld a, b
	sbc a, #0xff
	jp p, g32c
	ld b, #0xff
	ld c, #0xe0
g32c:

;if(x > 255)
;	x = 32
	ld a, #0xff
	sub a, c
	ld a, #0x00
	sbc a, b
	jp p, g255c
	ld b, #0x00
	ld c, #0xff
g255c:

;if(x >= 0)
;{
;	sprite->x = x;
;	sprite->tag &= 0xf;
;}
;else
;{
;	sprite->x = x + 32;
;	sprite->tag |= 0x80;
;}
	bit 7, b
	jp z, g0c
	set 7, 3(iy)
	ld a, c
	add a, #32
	ld c, a
	jr g0cc
g0c:
	ld a, #0xf
	and a, 3(iy)
	ld 3(iy), a
g0cc:
	ld 1(iy), c

	jp(hl)

