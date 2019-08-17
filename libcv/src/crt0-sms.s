; crt0.s for Colecovision cart

	.module crt0
	.globl _main
	.globl _cv_init
	.globl _cv_spint_handler
	.globl _cv_vint
	.globl _cv_start
	.globl ___sdcc_call_hl

	.area _HEADER(ABS)
	.org 0x0000

	jp	_cv_start

	.org 0x0038
	jp	vint

	.org 0x0066
	jp	pint

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
	ld sp, #0xe000			; Set stack pointer directly above top of memory.
	im	1

	call gsinit			; Initialize global and static variables.

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
	ei
	reti

pint:
	push	af
	push	bc
	push	de
	push	hl
	push	iy
	
	pop	iy
	pop	hl
	pop	de
	pop	bc
	pop	af
	retn

	.area   _GSINIT
gsinit::

; Delay for Mark III
    ld d, #0x04
label0:
    ld e, #0xff
label1:
    ld a, #0xff
label2:
    dec a
    jp NZ, label2
    dec	e
    jp NZ, label1
    dec d
    jp NZ, label0

	; Implicitly zeroed global and static variables.
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

