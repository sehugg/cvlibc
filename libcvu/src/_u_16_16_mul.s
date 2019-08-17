.module u_16_16_mul

.globl __u_16_16_mul

; uint32_t _u_16_16_mul(uint16_t l, uint16_t r);

.area _CODE

; 8x8->16 multiplication, takes arguments in e, h, returns result in hl. d has to be 0 before call.
u_16_16_mul_8_8:
	ld	l,d
	ld      b,#8
muluchar_rrx_s_loop:
	add     hl,hl
	jr      nc,muluchar_rrx_s_noadd
	add     hl,de
muluchar_rrx_s_noadd:
	djnz    muluchar_rrx_s_loop
	ret

; 16x16->32 multiplication
__u_16_16_mul:
	; setup iy for stack access.
	ld	iy,#0
	add	iy,sp

	; need one 32-bit local variable on stack.
	
	ld	d,#0

	; Multiplication of upper bytes
	ld	e,3 (iy)
	ld	h,5 (iy)
	call	u_16_16_mul_8_8
	push	hl

	; Multiplication of lower bytes
	ld	e,2 (iy)
	ld	h,4 (iy)
	call	u_16_16_mul_8_8
	push	hl

	; Mixed multiplications - add them together, add them to the result.
	ld	e,3 (iy)
	ld	h,4 (iy)
	call	u_16_16_mul_8_8
	ld	c,l
	ld	a,h
	ld	e,2 (iy)
	ld	h,5 (iy)
	call	u_16_16_mul_8_8
	ld	b,a
	add	hl,bc
	ld	d,-1 (iy)
	jr	NC,forward
	inc	d
forward:
	ld	c,-3 (iy)
	ld	b,-2 (iy)
	add	hl,bc
	jr	NC,forward2
	inc	d
forward2:
	ld	e,h
	ld	h,l
	ld	l,-4 (iy)

	ld	sp,iy
	ret

