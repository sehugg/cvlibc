CC = sdcc
CFLAGS = -mz80 -c "-I../../include/" --std-c99
PNG2CVS = png2cvs # Change to ../../../png2cvs/png2cvs or whatever if not installed.

.PHONY: all clean

all: main.rel cursor.png.sprite.rel
	$(CC) -mz80 --no-std-crt0 --code-loc 0x8100 --data-loc 0x7000 "../../bin/libcvu.lib" ../../bin/libcv.lib ../../bin/crt0.rel *.rel -o CursorSmooth.ihx ; objcopy --input-target=ihex --output-target=binary CursorSmooth.ihx CursorSmooth.rom

cursor.png.sprite.rel: cursor.png.sprite.c
	$(CC) $(CFLAGS) cursor.png.sprite.c
cursor.png.sprite.c: cursor.png
	$(PNG2CVS) --big --outfile cursor.png.sprite.c cursor.png

main.rel: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -f *.rel *.map *.lst *.lnk *.lk *.sym *.asm *~ *.rel *.noi *.ihx *.sprite.*

