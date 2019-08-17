CC = sdcc
CFLAGS = -mz80 -c "-I../../include/" --std-c99
CFLAGS-SMS = $(CFLAGS) -DCV_SMS
AS = as-z80
AFLAGS = -plosgff
PNG2CVS = png2cvs # Change to ../../../png2cvs/png2cvs or whatever if not installed.

.PHONY: all clean

all: Stars.rom Stars.sms

Stars.rom: main.rel
	$(CC) -mz80 --no-std-crt0 --code-loc 0x8100 --data-loc 0x7000 ../../bin/libcvu.lib ../../bin/libcv.lib ../../bin/crt0.rel main.rel -o Stars.ihx ; objcopy --input-target=ihex --output-target=binary Stars.ihx Stars.rom

Stars.sms: main-sms.rel
	$(CC) -mz80 --no-std-crt0 --code-loc 0x0100 --data-loc 0xc000 ../../bin/libcvu-sms.lib ../../bin/libcv-sms.lib ../../bin/crt0-sms.rel main-sms.rel -o Stars-sms.ihx ; objcopy --input-target=ihex --output-target=binary Stars-sms.ihx Stars.sms

main.rel: main.c
	$(CC) $(CFLAGS) main.c

main-sms.rel: main.c
	$(CC) $(CFLAGS-SMS) main.c -o main-sms.rel

clean:
	rm -f *.rel *.map *.lst *.lnk *.sym *.asm *~ *.rel *.noi *.ihx *.sprite.* *.lk

