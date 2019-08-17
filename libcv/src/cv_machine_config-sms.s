; (c) 2016 Philipp Krause philipp@colecovision.eu

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

.module cv_machine_config

.globl _cv_machine_config

.area	_DATA
	_cv_machine_config:
	.ds 1

.area   _GSINIT
	; Check machine type by memory aliasing
	ld	hl, #0xc3ff
	ld	b, (hl)	; Backup previous memory contents
	ld	a, #0x55
	ld	(hl), a
	ex	de, hl
	ld	hl, #0xc7ff ; (#0xc7ff) aliases with (#0xc3ff) on SG-1000
	cp	a, (hl)
	jr	nz, notSG1000
	ex	de, hl
	ld	a, #0xaa
	ld	(hl), a
	ex	de, hl
	cp	a, (hl)
	jr	z, end ; if we jump from here, (#0xc3ff) is the same as (#0xc7ff), i.e. we are running on a Sega SG-1000 or similar.
notSG1000:
	ld	hl, #0xcbff	; (#0xcbff) aliases with (#0xc3ff) on SC-3000
	cp	a, (hl)
	jr	nz, notSC3000
	ex	de, hl
	ld	a, #0x55
	ld	(hl), a
	ex	de, hl
	cp	a, (hl)
	jr	nz, notSC3000
	; if we reach here, (#0xc3ff) is the same as (#0xcbff), i.e. we are running on a Sega SC-3000 or similar.
	ld	a, #0x40
	jr	endset
notSC3000:
	; if we reach here, we are running on a Sega Mark III or Master System or similar.
	ld	a, #0x80
endset:
	ld (_cv_machine_config), a
end:
	ex	de, hl
	ld	(hl), b

