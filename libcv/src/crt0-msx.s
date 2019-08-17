; crt0.s for Colecovision cart

	.module crt0
	.globl _main
	.globl _cv_init
	.globl _cv_spint_handler
	.globl _cv_vint
	.globl _cv_start
	.globl ___sdcc_call_hl

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
; MSX cartridge header @ 0x4000 - 0x400f
	.dw 0x4241
        .dw _cv_start
        .dw _cv_start
        .dw 0
        .dw 0
        .dw 0
        .dw 0
        .dw 0

_cv_start:
	di
	ld sp, #0xe000			; Set stack pointer directly above top of memory.
	im	1

	call gsinit			; Initialize global and static variables.
	call vinthook
	call _cv_init			; Initialize Colecovision specific stuff.
	call _main
	rst 0x0				; Restart when main() returns.

	.area   _GSINIT
gsinit::

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

; set up timer hook
H_TIMI = 0xFD9F
vinthook:
	ld	a,#0xc3
	ld	(H_TIMI),a
	ld	a, #<(_cv_vint)
	ld	(H_TIMI+1),a
	ld	a, #>(_cv_vint)
	ld	(H_TIMI+2),a
	ret
