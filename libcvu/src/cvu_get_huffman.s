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

.module cvu_get_huffman

.globl _cvu_get_huffman

; uint8_t cvu_get_huffman(struct cvu_huffman_state *state);

_cvu_get_huffman:
	pop hl
	pop iy
	push iy
	push hl

	; current = state->root;
	ld b, #0
	ld c, 4(iy)

	ld e, 8(iy)	; load state->bit
	ld d, 9(iy)	; load state->buffer
	
	; for(;;)
	; {
for:

	; state->buffer >>= 1;
	srl d

	; if(state->bit == 8)
	; {
	ld a, #8
	cp a, e
	jp nz, #next1

	; state->buffer = (state->input)();
	push iy
	push bc
	ld hl, #next2
	push hl
	ld l, 0(iy)
	ld h, 1(iy)
	jp (hl)
next2:
	pop bc
	pop iy
	ld d, l

	; state->bit = 0;
	ld e, #0

	; }
next1:

	; state->bit++;
	inc e

	; if(!(state->buffer & 0x01))	// Left
	; {
	; if(current >= state->ls && current < state->rs)
	; {
	; ret = state->nodes[current].left;
	; break;
	; }
	; current = state->nodes[current].left;
	; }
	; else	// Right
	; {
	; if(current >= state->bs)
	; {
	; ret = state->nodes[current].right;
	; break;
	; }
	; current = state->nodes[current].right;
	; }

	ld l, 2(iy)
	ld h, 3(iy)
	add hl, bc
	add hl, bc	; &(state->nodes[current]) in hl
	ld a, #1
	and a, d
	ld a, c
	jr nz, #right
left:
	cp a, 5(iy)
	jr c, next3
	cp a, 7(iy)
	jr c, end
next3:
	ld c, (hl)
	jp for
right:
	inc hl
	cp a, 6(iy)
	jp c, next3

	; return(ret);
end:
	ld 8(iy), e	; store state->bit
	ld 9(iy), d	; store state->buffer
	ld l, (hl)
	ret




	
	
