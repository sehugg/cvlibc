; crt0.s for Colecovision cart

	.module crt0
	.globl _main
	.globl _cv_init
	.globl _cv_spint_handler
	.globl _cv_vint
	.globl _cv_start
	.globl ___sdcc_call_hl

	.area _HEADER(ABS)
	.org 0x8000

	.db 0x55, 0xaa			; Title screen and 12 second delay - swap 0x55 and 0xaa not to skip it.
	.dw 0								; Sprite name table for BIOS
	.dw 0								; Sprite order table for BIOS.
	.dw 0								; Buffer for BIOS.
	.dw 0								; Controller map for BIOS.
	.dw _cv_start						; where to start execution of program.
	jp	0x0		; RST 0x08			
	jp	0x0		; RST 0x10
	jp	0x0		; RST 0x18
	jp	0x0		; RST 0x20
	jp	0x0		; RST 0x28
	jp	0x0		; RST 0x30
	jp spint	; RST 0x38 - spinner - maskable interrupt
	jp vint		; Vertical retrace - NMI
	.ascii " / / NOT"

	; Ordering of segments for the linker - copied from sdcc crt0.s
	.area	_CODE
	.area	_INITIALIZER
	.area	_HOME
	.area	_GSINIT
	.area	_GSFINAL
	.area	_DATA
	.area	_INITIALIZED
	.area	_BSEG
	.area	_BSS
	.area	_HEAP

	.area	_CODE

_cv_start:
	di
	ld sp, #0x7400			; Set stack pointer directly above top of memory.
	im	1

	call gsinit				; Initialize global and static variables.

	call _cv_init			; Initialize Colecovision specific stuff.
	call _main
	rst 0x0				; Restart when main() returns.

vint:
	push	af
	push	bc
	push	de
	push	hl
	push	iy
	call	_cv_vint
	pop	iy
	pop	hl
	pop	de
	pop	bc
	pop	af
	retn

spint:
	push	hl
	ld	hl, (#_cv_spint_handler)
	ld	a, l
	or	a, h
	jr	Z, skip
	push	af
	push	bc
	push	de
	push	iy
	in	a, (#0xfc)
	ld	c, a
	in	a, (#0xff)
	ld	b, a
	push	bc
	call	___sdcc_call_hl
	pop	af
	pop	iy
	pop	de
	pop	bc
	pop	af
skip:
	pop	hl
	ei
	reti

	.area   _GSINIT
gsinit::
	ld	bc, #l__DATA
	ld	a, b
	or	a, c
	jr	Z, zeroed_data
	ld	hl,	#s__DATA
	ld	(hl), #0x00
	dec	bc
	ld	a, b
	or	a, c
	jr	Z, zeroed_data
	ld	e, l
	ld	d, h
	inc	de
	ldir
zeroed_data:

	; Explicitly initialized global variables.
	ld	bc, #l__INITIALIZER
	ld	a, b
	or	a, c
	jr	Z, gsinit_static
	ld	de, #s__INITIALIZED
	ld	hl, #s__INITIALIZER
	ldir

gsinit_static:
	; Explicitly initialized static variables inserted by compiler here.

	.area   _GSFINAL
	ret

	.area _HOME

