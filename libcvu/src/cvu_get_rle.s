; (c) 2006 Philipp Klaus Krause philipp@colecovision.eu

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

.module cvu_get_rle

.globl _cvu_get_rle

; uint8_t cvu_get_rle(struct cvu_rle_state *state);

_cvu_get_rle:
	pop hl
	pop iy
	push iy
	push hl

	; if(state->left)
	; goto output;
	ld a, 3(iy)
	or a
	jp nz, output

	; next = (state->input)();
	push iy
	ld hl, #next1
	push hl
	ld l, 0(iy)
	ld h, 1(iy)
	jp (hl)
next1:
	pop iy

	; if(next != state->escape)
	;	return(next);
	ld a, 2(iy)
	cp a, l
	ret nz

	; state->left = (state->input)();
	push iy
	ld hl, #next2
	push hl
	ld l, 0(iy)
	ld h, 1(iy)
	jp (hl)
next2:
	pop iy
	ld 3(iy), l

	; state->buffer = (state->input)();
	push iy
	ld hl, #next3
	push hl
	ld l, 0(iy)
	ld h, 1(iy)
	jp (hl)
next3:
	pop iy
	ld 4(iy), l

	; output:
output:

	; state->left--;
	dec 3(iy)

	; return(state->buffer);
	ld l, 4(iy)
	ret

