CC = sdcc
CFLAGS = -mz80 -c "-I../../include/" --std-c99
CFLAGS-SMS = $(CFLAGS) -DCV_SMS
PNG2CVS = png2cvs # Change to ../../../png2cvs/png2cvs or whatever if not installed.

.PHONY: all clean

all: Cursor.rom Cursor.sms

Cursor.rom: main.rel cursor.png.sprite.rel
	$(CC) -mz80 --no-std-crt0 --code-loc 0x8100 --data-loc 0x7000 ../../bin/libcvu.lib ../../bin/libcv.lib ../../bin/crt0.rel main.rel cursor.png.sprite.rel -o Cursor32.ihx ; objcopy --input-target=ihex --output-target=binary Cursor32.ihx Cursor32.rom

Cursor.sms: main-sms.rel cursor.png.sprite.rel
	$(CC) -mz80 --no-std-crt0 --code-loc 0x0100 --data-loc 0xc000 ../../bin/libcvu-sms.lib ../../bin/libcv-sms.lib ../../bin/crt0-sms.rel main-sms.rel cursor.png.sprite.rel -o Cursor32-sms.ihx ; objcopy --input-target=ihex --output-target=binary Cursor32-sms.ihx Cursor32.sms

cursor.png.sprite.rel: cursor.png.sprite.c
	$(CC) $(CFLAGS) cursor.png.sprite.c
cursor.png.sprite.c: cursor.png
	$(PNG2CVS) --big --outfile cursor.png.sprite.c cursor.png

main.rel: main.c
	$(CC) $(CFLAGS) main.c
main-sms.rel: main.c
	$(CC) $(CFLAGS-SMS) main.c -o main-sms.rel

clean:
	rm -f *.rel *.map *.lst *.lnk *.sym *.asm *~ *.rel *.noi *.ihx *.sprite.* *.lk

