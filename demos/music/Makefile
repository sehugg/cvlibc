CC = sdcc
CVLIBPATH = "../.."
CFLAGS = --opt-code-size --fverbose-asm --std-c99 -mz80 -c -I$(CVLIBPATH)/include/
CFLAGS-SMS = $(CFLAGS) -DCV_SMS
SED = sed
ABC2CVM = abc2cvm
PNG2CV = png2cv

DUETS = 1 3 4 7 9 10
MUSICOBJ = $(DUETS:%=12duets.abc.%.1.music.rel) $(DUETS:%=12duets.abc.%.2.music.rel)

.PHONY: all clean

all: Music.rom Music.sms

Music.rom: main.rel $(MUSICOBJ)
	$(CC) -mz80 --no-std-crt0 --code-loc 0x8100 --data-loc 0x7000 $(CVLIBPATH)/bin/libcvu.lib ../../bin/libcv.lib ../../bin/crt0.rel main.rel $(MUSICOBJ) -o Music.ihx; objcopy --input-target=ihex --output-target=binary Music.ihx Music.rom
Music.sms: main-sms.rel tiles.png.pattern.rel $(MUSICOBJ)
	$(CC) -mz80 --no-std-crt0 --code-loc 0x0100 --data-loc 0xc000 $(CVLIBPATH)/bin/libcvu-sms.lib ../../bin/libcv-sms.lib ../../bin/crt0-sms.rel main-sms.rel tiles.png.pattern.rel $(MUSICOBJ) -o Music-sms.ihx; objcopy --input-target=ihex --output-target=binary Music-sms.ihx Music.sms

main.rel: main.c
	$(CC) $(CFLAGS) main.c
main-sms.rel: main.c
	$(CC) $(CFLAGS-SMS) main.c -o main-sms.rel

12duets.abc.%.1.c: 12duets.abc
	$(ABC2CVM) -X $* -V 1 12duets.abc

12duets.abc.%.2.c: 12duets.abc
	$(ABC2CVM) -X $* -V 2 12duets.abc

12duets.abc.%.1.music.c: 12duets.abc.%.1.c
	$(SED) -e 's/notes/duet_$*_1/' $< > $@

12duets.abc.%.2.music.c: 12duets.abc.%.2.c
	$(SED) -e 's/notes/duet_$*_2/' $< > $@

12duets.abc.%.1.music.rel: 12duets.abc.%.1.music.c
	$(CC) $(CFLAGS) $<

12duets.abc.%.2.music.rel: 12duets.abc.%.2.music.c
	$(CC) $(CFLAGS) $<

tiles.png.pattern.rel: tiles.png.pattern.c
	$(CC) $(CFLAGS-SMS) tiles.png.pattern.c
tiles.png.pattern.c: tiles.png
	$(PNG2CV) tiles.png

clean:
	rm -f *.rel *.map *.lst *.lnk *.lk *.sym *.asm *~ *.o *.rel *.noi *.ihx *.abc.*.c

