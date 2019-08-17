; (c) 2010 Philipp Klaus Krause philipp@colecovision.eu

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

.module cvu_cmul

.globl _cvu_cmul

; void cvu_cmul(struct cvu_c * l, const struct cvu_c * r)
;{
;	cvu_f tmp;
;	tmp = fmul2(l->r, r->r) - fmul2(l->i, r->i);
;	l->i = fmul2(l->r, r->i) + fmul2(r->r, l->i);
;	l->r = tmp;
;}

_cvu_cmul:
	; Get l into ix, r into iy.
	push	ix
	pop	bc
	pop	hl
	pop	ix
	pop	iy
	push	iy
	push	ix
	push	hl
	push	bc

	; Multiply imaginary components
	push iy
	ld	l,2 (iy)
	ld	h,3 (iy)
	push	hl
	ld	l,2 (ix)
	ld	h,3 (ix)
	push	hl
	call	_cvu_fmul2
	pop	af
	pop	af
	pop	iy
	push	hl
	
	; Multiply real components
	push	iy
	ld	l,0 (iy)
	ld	h,1 (iy)
	push	hl
	ld	l,0 (ix)
	ld	h,1 (ix)
	push	hl
	call	_cvu_fmul2
	pop	af
	pop	af
	pop	iy
	
	; Get real part of result onto stack.
	pop	bc
	xor	a, a
	sbc	hl, bc
	push	hl

	; Mixed multiplication.
	push	iy
	ld	l,2 (iy)
	ld	h,3 (iy)
	push	hl
	ld	l,0 (ix)
	ld	h,1 (ix)
	push	hl
	call	_cvu_fmul2
	pop	af
	pop	af
	pop	iy
	push	hl

	; Mixed multiplication.
	ld	l,0 (iy)
	ld	h,1 (iy)
	push	hl
	ld	l,2 (ix)
	ld	h,3 (ix)
	push	hl
	call	_cvu_fmul2
	pop	af
	pop	af

	; Get imaginary part of result into hl.
	pop	bc
	add	hl,bc

	; Store imaginary part of result.
	ld	2 (ix), l
	ld	3 (ix), h

	; Store real part of result.
	pop	hl
	ld	0 (ix), l
	ld	1 (ix), h

	pop	ix
	ret

